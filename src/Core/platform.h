#ifndef PLATFORM_H
#define PLATFORM_H

// 森林和河流绘制函数
void drawRiver();
void drawForestGround();

// 河流路径生成函数
void generateRiverPath(float x, float& z);
void getRiverTangent(float t, float& tangentX, float& tangentZ);

#endif