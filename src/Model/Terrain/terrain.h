#pragma once
#include "headers.h"
#include <vector>
#include <cmath>

// 【新增】树木实例结构体
struct TreeInstance {
    float x, y, z;
    float scale;
    float rotation;
    bool isPine; // true=松树, false=圆树
};

class TerrainSystem {
public:
    void init();
    void draw();

    // 获取指定坐标(x, z)处的地面高度 y
    float getHeight(float x, float z);

private:
    // 使用显示列表优化性能 (绘制几千棵树如果不优化会卡顿)
    GLuint terrainList;
    std::vector<TreeInstance> treeInstances;

    // 内部绘制函数
    void generateVegetationData();
    void drawPineTree(float snowFactor);
    void drawRoundTree(float snowFactor);
    void drawTerrainMesh();
    void drawTrees();
    void drawRocks();

    // 辅助：计算地形法线以实现柔和光照
    void setNormalForPoint(float x, float z);


};

extern TerrainSystem terrainSystem;