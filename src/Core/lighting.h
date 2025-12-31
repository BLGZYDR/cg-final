#pragma once
#include "headers.h"
#include <cmath>
#include <iostream>

// 光照系统类
class LightingSystem {
public:
    LightingSystem();

    // 初始化光照
    void init();

    // 更新时间、太阳/月亮位置
    void update(float deltaTime);

    // 应用光照到场景（每帧调用）
    void applyLighting();

    // 绘制太阳和月亮的光球（可视化光源）
    void drawLightOrbs();

    // 辅助函数：设置物体材质 (Phong模型)
    // ambient: 环境光系数, diffuse: 漫反射颜色, specular: 高光颜色, shininess: 高光硬度
    void setMaterial(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess);

    // 预设材质辅助函数
    void setMaterialWater();
    void setMaterialGrass();
    void setMaterialSnow();
    void setMaterialStone();

    // 获取当前是否为白天（用于其他逻辑判断）
    bool isDaytime() const;

private:
    float dayTime;          // 当前时间 (0 - 24)
    float timeSpeed;        // 时间流逝速度
    float sunAngle;         // 太阳角度 (弧度)

    // 光源位置
    GLfloat sunPos[4];
    GLfloat moonPos[4];

    // 颜色变量
    GLfloat globalAmbient[4];
    GLfloat sunColor[4];
    GLfloat moonColor[4];
    GLfloat skyColor[4];

    // 私有辅助：线性插值颜色
    void lerpColor(GLfloat* out, const GLfloat* a, const GLfloat* b, float t);
};

// 声明全局实例
extern LightingSystem lightingSystem;