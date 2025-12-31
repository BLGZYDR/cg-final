#ifndef GEOMETRY_H
#define GEOMETRY_H


// 长方体（矩形柱体）顶点
extern double cuboidVertices[8][3];
// 梯形柱体顶点
extern double trapezoidalPrismVertices[8][3];


// 绘制球体，参数为球心 (x, y, z)、半径、纬度分段数、经度分段数
void DrawSphere(double radius, int latitudeSegments, int longitudeSegments, double centerX, double centerY, double centerZ);

// 生成梯形柱体的顶点
void GenerateTrapezoidalPrism(double baseX, double baseY, double baseZ, double width, double height, double depth);
// 根据已生成的顶点渲染梯形柱体
void RenderTrapezoidalPrism();

// 生成长方体（矩形柱体）的顶点
void GenerateCuboid(double baseX, double baseY, double baseZ, double width, double height, double depth);
// 根据已生成的顶点渲染长方体
void RenderCuboid();

// 生成平行四边形柱体的顶点（底面为 x-y 平面上的平行四边形）
void GenerateParallelogramPrism(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double zBase, double height);
// 根据已生成的顶点渲染平行四边形柱体
void RenderParallelogramPrism();

// 生成三角柱的顶点（底面为 x-y 平面上的三角形）
void GenerateTriangularPrism(double x1, double y1, double x2, double y2, double x3, double y3, double zBase, double height);
// 根据已生成的顶点渲染三角柱
void RenderTriangularPrism();

#endif