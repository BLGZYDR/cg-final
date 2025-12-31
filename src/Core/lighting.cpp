#include "lighting.h"
#include <algorithm> 
#include <iterator> 
#include <cmath> // 确保包含数学库

LightingSystem lightingSystem;

LightingSystem::LightingSystem() {
    dayTime = 12.0f;
    timeSpeed = 0.5f;
    sunAngle = 0.0f;

    for (int i = 0; i < 4; i++) {
        sunPos[i] = 0.0f;
        moonPos[i] = 0.0f;
        globalAmbient[i] = 0.0f;
        sunColor[i] = 0.0f;
        moonColor[i] = 0.0f;
        skyColor[i] = 0.0f;
    }
}

void LightingSystem::init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void LightingSystem::lerpColor(GLfloat* out, const GLfloat* a, const GLfloat* b, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    out[0] = a[0] + (b[0] - a[0]) * t;
    out[1] = a[1] + (b[1] - a[1]) * t;
    out[2] = a[2] + (b[2] - a[2]) * t;
    out[3] = a[3] + (b[3] - a[3]) * t;
}

void LightingSystem::update(float deltaTime) {
    // 1. 更新时间
    dayTime += deltaTime * timeSpeed;
    if (dayTime >= 24.0f) dayTime -= 24.0f;

    // 2. 计算角度
    float angle = (dayTime - 6.0f) * (3.14159f / 12.0f);
    sunAngle = angle;

    // 3. 计算光源方向向量 (注意：这里不需要很大的 radius，因为是方向向量)
    float radius = 1000.0f;

    sunPos[0] = cos(angle) * radius;
    sunPos[1] = sin(angle) * radius;
    sunPos[2] = 0.0f;
    // 【关键修改 1】 w = 0.0f 表示定向光(Directional Light/Infinite distance)
    // 这样就不会在场景中间产生“灯泡”亮斑，而是均匀的平行光
    sunPos[3] = 0.0f;

    // 月亮位置
    moonPos[0] = -sunPos[0];
    moonPos[1] = -sunPos[1];
    moonPos[2] = -sunPos[2];
    // 【关键修改 2】 月亮也设为定向光
    moonPos[3] = 0.0f;

    // 4. 计算颜色 (保持不变)
    const GLfloat colBlueSky[] = { 0.53f, 0.81f, 0.92f, 1.0f };
    const GLfloat colSunset[] = { 0.8f, 0.4f, 0.2f, 1.0f };
    const GLfloat colNight[] = { 0.05f, 0.05f, 0.1f, 1.0f };

    const GLfloat lightDay[] = { 1.0f, 0.95f, 0.9f, 1.0f };
    const GLfloat lightSunset[] = { 0.8f, 0.5f, 0.2f, 1.0f };
    const GLfloat lightNight[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    const GLfloat moonLight[] = { 0.2f, 0.3f, 0.4f, 1.0f };

    if (dayTime >= 5.0f && dayTime < 19.0f) {
        float t = 1.0f;
        if (dayTime < 7.0f) {
            t = (dayTime - 5.0f) / 2.0f;
            lerpColor(skyColor, colNight, colBlueSky, t);
            lerpColor(sunColor, lightSunset, lightDay, t);
            GLfloat ambDay[] = { 0.4f, 0.4f, 0.4f, 1.0f };
            GLfloat ambNight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
            lerpColor(globalAmbient, ambNight, ambDay, t);
        }
        else if (dayTime > 17.0f) {
            t = (dayTime - 17.0f) / 2.0f;
            lerpColor(skyColor, colBlueSky, colSunset, t);
            lerpColor(sunColor, lightDay, lightSunset, t);
            GLfloat ambDay[] = { 0.4f, 0.4f, 0.4f, 1.0f };
            GLfloat ambSunset[] = { 0.3f, 0.3f, 0.3f, 1.0f };
            lerpColor(globalAmbient, ambDay, ambSunset, t);
        }
        else {
            for (int i = 0; i < 4; i++) skyColor[i] = colBlueSky[i];
            for (int i = 0; i < 4; i++) sunColor[i] = lightDay[i];
            globalAmbient[0] = 0.4f; globalAmbient[1] = 0.4f; globalAmbient[2] = 0.4f; globalAmbient[3] = 1.0f;
        }
        moonColor[0] = 0; moonColor[1] = 0; moonColor[2] = 0; moonColor[3] = 1;
    }
    else {
        float t = 1.0f;
        if (dayTime >= 19.0f && dayTime < 21.0f) {
            t = (dayTime - 19.0f) / 2.0f;
            lerpColor(skyColor, colSunset, colNight, t);
            sunColor[0] = 0; sunColor[1] = 0; sunColor[2] = 0;
            lerpColor(moonColor, lightNight, moonLight, t);
        }
        else if (dayTime >= 4.0f && dayTime < 5.0f) {
            lerpColor(skyColor, colNight, colSunset, (dayTime - 4.0f));
            for (int i = 0; i < 4; i++) moonColor[i] = moonLight[i];
        }
        else {
            for (int i = 0; i < 4; i++) skyColor[i] = colNight[i];
            for (int i = 0; i < 4; i++) moonColor[i] = moonLight[i];
            sunColor[0] = 0;
        }
        globalAmbient[0] = 0.1f; globalAmbient[1] = 0.1f; globalAmbient[2] = 0.15f; globalAmbient[3] = 1.0f;
    }
}

void LightingSystem::applyLighting() {
    glClearColor(skyColor[0], skyColor[1], skyColor[2], skyColor[3]);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // 设置太阳 (GL_LIGHT0)
    if (sunPos[1] > -200.0f) {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sunColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sunColor);
        GLfloat sunAmb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmb);
    }
    else {
        glDisable(GL_LIGHT0);
    }

    // 设置月亮 (GL_LIGHT1)
    if (moonPos[1] > -200.0f) {
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, moonPos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, moonColor);
        glLightfv(GL_LIGHT1, GL_SPECULAR, moonColor);
        GLfloat moonAmb[] = { 0.05f, 0.05f, 0.1f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, moonAmb);
    }
    else {
        glDisable(GL_LIGHT1);
    }
}

void LightingSystem::drawLightOrbs() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // 【关键修改 3】 可视化距离
    // 将视觉上的太阳/月亮推到地形范围之外 (地形半径2000，这里推到6000)
    // 这样就不会穿模，也不会觉得近
    float drawDistance = 6.0f;

    // 绘制太阳
    if (sunPos[1] > -500.0f) {
        glPushMatrix();
        // sunPos 本身是1000半径，乘以6变成6000半径
        glTranslatef(sunPos[0] * drawDistance, sunPos[1] * drawDistance, sunPos[2] * drawDistance);
        glColor3fv(sunColor);
        // 球体也要画大一点才能看清
        glutSolidSphere(300.0, 16, 16);
        glPopMatrix();
    }

    // 绘制月亮
    if (moonPos[1] > -500.0f) {
        glPushMatrix();
        glTranslatef(moonPos[0] * drawDistance, moonPos[1] * drawDistance, moonPos[2] * drawDistance);
        glColor3f(0.9f, 0.9f, 1.0f);
        glutSolidSphere(200.0, 16, 16);
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void LightingSystem::setMaterial(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void LightingSystem::setMaterialWater() {
    GLfloat mat_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
    GLfloat mat_diffuse[] = { 0.4f, 0.6f, 0.9f, 0.6f };
    GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat shininess = 100.0f;
    setMaterial(mat_ambient, mat_diffuse, mat_specular, shininess);
}

bool LightingSystem::isDaytime() const {
    return (dayTime > 6.0f && dayTime < 18.0f);
}