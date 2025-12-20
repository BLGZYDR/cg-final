#include "house.h"
#include "headers.h"
#include "geometry.h"
#include "texture.h"

void drawHouse() {
    // 绘制土地地基
    glPushMatrix();
    applyDirtTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(40, 40, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateCuboid(-1, -10, -1, 802, 19, 802);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 房子四面墙壁
    glPushMatrix();
    applyWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // 房子后墙
    GenerateTrapezoidalPrism(320, 10, 100, 80, 160, 10);
    RenderTrapezoidalPrism();
    GenerateTrapezoidalPrism(480, 10, 100, -80, 160, 10);
    RenderTrapezoidalPrism();

    // 房子前墙
    GenerateTriangularPrism(320, 90, 385, 90, 385, 155, 260, 10);
    RenderTriangularPrism();
    GenerateTriangularPrism(480, 90, 415, 90, 415, 155, 260, 10);
    RenderTriangularPrism();
    GenerateTriangularPrism(385, 155, 415, 155, 400, 170, 260, 10);
    RenderTriangularPrism();
    GenerateCuboid(385, 90, 260, 30, 10, 10);
    RenderCuboid();
    GenerateCuboid(385, 130, 260, 30, 25, 10);
    RenderCuboid();
    GenerateCuboid(320, 10, 260, 20, 80, 10);
    RenderCuboid();
    GenerateCuboid(460, 10, 260, 20, 80, 10);
    RenderCuboid();
    GenerateCuboid(340, 10, 260, 30, 40, 10);
    RenderCuboid();
    GenerateCuboid(430, 10, 260, 35, 40, 10);
    RenderCuboid();
    GenerateCuboid(370, 10, 260, 15, 70, 10);
    RenderCuboid();
    GenerateCuboid(415, 10, 260, 15, 70, 10);
    RenderCuboid();
    GenerateCuboid(340, 80, 260, 140, 10, 10);
    RenderCuboid();
    GenerateCuboid(385, 70, 260, 30, 10, 10);
    RenderCuboid();

    // 房子左墙
    GenerateTrapezoidalPrism(320, 80, 100, 10, 20, 160);
    RenderTrapezoidalPrism();
    GenerateCuboid(320, 10, 100, 10, 70, 70);
    RenderCuboid();
    GenerateCuboid(320, 10, 200, 10, 70, 60);
    RenderCuboid();
    GenerateCuboid(320, 10, 170, 10, 40, 30);
    RenderCuboid();

    // 房子右墙
    GenerateTrapezoidalPrism(480, 80, 110, -10, 20, 150);
    RenderTrapezoidalPrism();
    GenerateCuboid(480, 10, 110, -10, 70, 60);
    RenderCuboid();
    GenerateCuboid(480, 10, 200, -10, 70, 60);
    RenderCuboid();
    GenerateCuboid(480, 10, 170, -10, 40, 30);
    RenderCuboid();

    disableTexture();
    glPopMatrix();

    // 绘制房顶
    glPushMatrix();
    applyBrickTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateParallelogramPrism(400, 170, 400, 180, 310, 80, 310, 90, 95, 180);
    RenderParallelogramPrism();
    GenerateParallelogramPrism(400, 170, 400, 180, 490, 80, 490, 90, 95, 180);
    RenderParallelogramPrism();

    // 绘制烟囱
    GenerateTrapezoidalPrism(350, 140, 170, -20, -40, 20);
    RenderTrapezoidalPrism();
    disableTexture();
    glPopMatrix();

    // 绘制大门
    glPushMatrix();
    applyDarkWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateCuboid(385, 20, 260, 30, 50, 5);
    RenderCuboid();
    disableTexture();

    // 绘制门上的装饰
    glColor3f(GRAY);
    GenerateCuboid(390, 25, 265, 20, 2, 0.5);
    RenderCuboid();
    GenerateCuboid(390, 65, 265, 20, -2, 0.5);
    RenderCuboid();
    GenerateCuboid(390, 44, 265, 20, 2, 0.5);
    RenderCuboid();
    GenerateCuboid(390, 25, 265, 2, 40, 0.5);
    RenderCuboid();
    GenerateCuboid(408, 25, 265, 2, 40, 0.5);
    RenderCuboid();

    // 绘制门前的棚子
    glPushMatrix();
    applyBrickTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateParallelogramPrism(400, 95, 400, 85, 370, 65, 370, 55, 270, 70);
    RenderParallelogramPrism();
    GenerateParallelogramPrism(400, 95, 400, 85, 430, 65, 430, 55, 270, 70);
    RenderParallelogramPrism();
    GenerateCuboid(375, 10, 330, 4, 57, 4);
    RenderCuboid();
    GenerateCuboid(425, 10, 330, -4, 57, 4);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    applyMarbleTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // 绘制入门走道
    GenerateCuboid(385, 10, 260, 30, 10, 60);
    RenderCuboid();
    GenerateCuboid(375, 10, 270, 10, 10, 50);
    RenderCuboid();
    GenerateCuboid(415, 10, 270, 10, 10, 50);
    RenderCuboid();

    // 绘制左边的围栏
    for (int i = 0; i < 6; i++) {
        GenerateCuboid(378, 20, 270 + i * 10, 4, 30, 4);
        RenderCuboid();
    }
    GenerateCuboid(378, 50, 270, 4, 4, 58);
    RenderCuboid();

    // 绘制右边围栏
    for (int i = 0; i < 6; i++) {
        GenerateCuboid(418, 20, 270 + i * 10, 4, 30, 4);
        RenderCuboid();
    }
    GenerateCuboid(418, 50, 270, 4, 4, 58);
    RenderCuboid();

    // 绘制台阶
    GenerateCuboid(375, 10, 320, 50, 10, 10);
    RenderCuboid();
    GenerateCuboid(385, 10, 330, 30, 5, 10);
    RenderCuboid();

    // 绘制房子地板
    GenerateCuboid(325, 10, 105, 150, 10, 150);
    RenderCuboid();

    // 绘制外围边缘
    GenerateCuboid(315, 10, 95, 170, 10, 5);
    RenderCuboid();
    GenerateCuboid(315, 10, 100, 5, 10, 175);
    RenderCuboid();
    GenerateCuboid(485, 10, 100, -5, 10, 175);
    RenderCuboid();
    GenerateCuboid(320, 10, 270, 65, 10, 5);
    RenderCuboid();
    GenerateCuboid(480, 10, 270, -65, 10, 5);
    RenderCuboid();

    // 绘制烟囱顶部边缘
    GenerateCuboid(355, 145, 165, -30, -10, 5);
    RenderCuboid();
    GenerateCuboid(355, 145, 190, -30, -10, 5);
    RenderCuboid();
    GenerateCuboid(355, 145, 170, -5, -10, 20);
    RenderCuboid();
    GenerateCuboid(330, 145, 170, -5, -10, 20);
    RenderCuboid();

    disableTexture();
    glPopMatrix();

    // 绘制房子内部装饰
    // 绘制床铺床板
    glPushMatrix();
    applyWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(40, 40, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateCuboid(330, 20, 110, 30, 20, 3);
    RenderCuboid();
    GenerateCuboid(330, 20, 113, 30, 10, 60);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 绘制被子
    glColor3f(WHITE);
    GenerateCuboid(330, 30, 113, 30, 10, 15);
    RenderCuboid();
    glColor3f(RED);
    GenerateCuboid(330, 30, 128, 30, 10, 45);
    RenderCuboid();

    // 绘制沙发
    // 绘制垫子
    glColor3f(WHITE);
    GenerateCuboid(470, 30, 150, -30, 10, 60);
    RenderCuboid();
    GenerateCuboid(470, 40, 150, -5, 12, 60);
    RenderCuboid();

    // 绘制木制底座
    glPushMatrix();
    applyWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(40, 40, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateCuboid(470, 20, 140, -30, 30, 10);
    RenderCuboid();
    GenerateCuboid(470, 20, 210, -30, 30, 10);
    RenderCuboid();
    GenerateCuboid(470, 20, 140, -30, 10, 80);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 绘制架子
    glPushMatrix();
    applyDarkWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    GenerateCuboid(470, 20, 220, -30, 2, 40);
    RenderCuboid();
    GenerateCuboid(470, 40, 220, -30, 2, 40);
    RenderCuboid();
    GenerateCuboid(470, 60, 220, -30, 2, 40);
    RenderCuboid();
    GenerateCuboid(470, 20, 220, -30, 42, 2);
    RenderCuboid();
    GenerateCuboid(470, 20, 258, -30, 42, 2);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 绘制地毯
    glPushMatrix();
    applyCarpetTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);
    GenerateCuboid(340, 20, 120, 130, 1, 130);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 绘制窗户玻璃
    glColor4f(WHITE, 0.2);
    // 正面窗户1
    GenerateCuboid(320, 50, 170, 10, 30, 30);
    RenderCuboid();
    // 正面窗户2
    GenerateCuboid(480, 50, 170, -10, 30, 30);
    RenderCuboid();
    // 正面窗户3
    GenerateCuboid(385, 100, 260, 30, 30, 10);
    RenderCuboid();
    // 左面窗户
    GenerateCuboid(340, 50, 260, 30, 30, 10);
    RenderCuboid();
    // 右面窗户
    GenerateCuboid(430, 50, 260, 30, 30, 10);
    RenderCuboid();

    // 绘制窗户边框
    glColor3f(BROWN);
    // 正面窗户边框1
    GenerateCuboid(380, 95, 270, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(380, 130, 270, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(380, 100, 270, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(415, 100, 270, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(399, 100, 270, 2, 30, 1);
    RenderCuboid();

    // 正面窗户边框2
    GenerateCuboid(335, 45, 270, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(335, 80, 270, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(335, 50, 270, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(370, 50, 270, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(354, 50, 270, 2, 30, 1);
    RenderCuboid();

    // 正面窗户边框3
    GenerateCuboid(425, 45, 270, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(425, 80, 270, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(425, 50, 270, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(460, 50, 270, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(444, 50, 270, 2, 30, 1);
    RenderCuboid();

    // 左面窗户边框
    GenerateCuboid(320, 45, 165, -1, 5, 40);
    RenderCuboid();
    GenerateCuboid(320, 85, 165, -1, -5, 40);
    RenderCuboid();
    GenerateCuboid(320, 50, 170, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(320, 50, 205, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(320, 50, 184, -1, 30, 2);
    RenderCuboid();

    // 右面窗户边框
    GenerateCuboid(481, 45, 165, -1, 5, 40);
    RenderCuboid();
    GenerateCuboid(481, 85, 165, -1, -5, 40);
    RenderCuboid();
    GenerateCuboid(481, 50, 170, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(481, 50, 205, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(481, 50, 184, -1, 30, 2);
    RenderCuboid();
}