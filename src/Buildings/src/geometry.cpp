// 各类几何体实现
#include "headers.h"
#include "geometry.h"

// 长方体（矩形柱体）顶点
double cuboidVertices[8][3];
// 梯形柱体顶点
double trapezoidalPrismVertices[8][3];
// 平行四边形柱体顶点
double parallelogramPrismVertices[8][3];
// 三角柱顶点
double triangularPrismVertices[6][3];
struct RiverVertex {
    float x, y, z;
    float u, v;  // 纹理坐标
};
static std::vector<RiverVertex> riverVertices;
static std::vector<unsigned int> riverIndices;

// 绘制球体，参数为球心 (centerX, centerY, centerZ)、半径、纬度分段数、经度分段数
void DrawSphere(double radius, int latitudeSegments, int longitudeSegments, double centerX, double centerY, double centerZ) {
    int i, j;
    for (i = 0; i <= latitudeSegments; i++) {
        double lat0 = PI * (-0.5 + (double)(i - 1) / latitudeSegments);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);
        double lat1 = PI * (-0.5 + (double)i / latitudeSegments);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        glBegin(GL_QUAD_STRIP);
        glScaled(100, 100, 100);
        for (j = 0; j <= longitudeSegments; j++) {
            double lng = 2 * PI * (double)(j - 1) / longitudeSegments;
            double x = cos(lng);
            double y = sin(lng);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(zr0, zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(zr1, zr1, z1);
        }
        glEnd();
    }
}

// 生成梯形柱体的顶点
void GenerateTrapezoidalPrism(double baseX, double baseY, double baseZ, double width, double height, double depth) {
    // 底面
    trapezoidalPrismVertices[0][0] = baseX;
    trapezoidalPrismVertices[0][1] = baseY;
    trapezoidalPrismVertices[0][2] = baseZ;

    trapezoidalPrismVertices[1][0] = baseX + width;
    trapezoidalPrismVertices[1][1] = baseY;
    trapezoidalPrismVertices[1][2] = baseZ;

    trapezoidalPrismVertices[2][0] = baseX + width;
    trapezoidalPrismVertices[2][1] = baseY + height;
    trapezoidalPrismVertices[2][2] = baseZ;

    trapezoidalPrismVertices[3][0] = baseX;
    trapezoidalPrismVertices[3][1] = baseY + height / 2;
    trapezoidalPrismVertices[3][2] = baseZ;

    // 顶面（z 方向平移）
    for (int i = 0; i < 4; i++) {
        trapezoidalPrismVertices[i + 4][0] = trapezoidalPrismVertices[i][0];
        trapezoidalPrismVertices[i + 4][1] = trapezoidalPrismVertices[i][1];
        trapezoidalPrismVertices[i + 4][2] = trapezoidalPrismVertices[i][2] + depth;
    }
}

// 生成长方体（矩形柱体）的顶点
void GenerateCuboid(double baseX, double baseY, double baseZ, double width, double height, double depth) {
    // 底面
    cuboidVertices[0][0] = baseX;
    cuboidVertices[0][1] = baseY;
    cuboidVertices[0][2] = baseZ;

    cuboidVertices[1][0] = baseX;
    cuboidVertices[1][1] = baseY;
    cuboidVertices[1][2] = baseZ + depth;

    cuboidVertices[2][0] = baseX + width;
    cuboidVertices[2][1] = baseY;
    cuboidVertices[2][2] = baseZ + depth;

    cuboidVertices[3][0] = baseX + width;
    cuboidVertices[3][1] = baseY;
    cuboidVertices[3][2] = baseZ;

    // 顶面（y 方向平移）
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 1)
                cuboidVertices[i + 4][j] = cuboidVertices[i][j] + height;
            else
                cuboidVertices[i + 4][j] = cuboidVertices[i][j];
        }
    }
}

// 根据已生成的顶点渲染梯形柱体
// 需先调用 GenerateTrapezoidalPrism 填充 trapezoidalPrism
void RenderTrapezoidalPrism() {
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(trapezoidalPrismVertices[0][0], trapezoidalPrismVertices[0][1], trapezoidalPrismVertices[0][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(trapezoidalPrismVertices[1][0], trapezoidalPrismVertices[1][1], trapezoidalPrismVertices[1][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(trapezoidalPrismVertices[2][0], trapezoidalPrismVertices[2][1], trapezoidalPrismVertices[2][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(trapezoidalPrismVertices[3][0], trapezoidalPrismVertices[3][1], trapezoidalPrismVertices[3][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(trapezoidalPrismVertices[1][0], trapezoidalPrismVertices[1][1], trapezoidalPrismVertices[1][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(trapezoidalPrismVertices[0][0], trapezoidalPrismVertices[0][1], trapezoidalPrismVertices[0][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(trapezoidalPrismVertices[4][0], trapezoidalPrismVertices[4][1], trapezoidalPrismVertices[4][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(trapezoidalPrismVertices[5][0], trapezoidalPrismVertices[5][1], trapezoidalPrismVertices[5][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(trapezoidalPrismVertices[7][0], trapezoidalPrismVertices[7][1], trapezoidalPrismVertices[7][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(trapezoidalPrismVertices[6][0], trapezoidalPrismVertices[6][1], trapezoidalPrismVertices[6][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(trapezoidalPrismVertices[3][0], trapezoidalPrismVertices[3][1], trapezoidalPrismVertices[3][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(trapezoidalPrismVertices[2][0], trapezoidalPrismVertices[2][1], trapezoidalPrismVertices[2][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(trapezoidalPrismVertices[5][0], trapezoidalPrismVertices[5][1], trapezoidalPrismVertices[5][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(trapezoidalPrismVertices[6][0], trapezoidalPrismVertices[6][1], trapezoidalPrismVertices[6][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(trapezoidalPrismVertices[2][0], trapezoidalPrismVertices[2][1], trapezoidalPrismVertices[2][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(trapezoidalPrismVertices[1][0], trapezoidalPrismVertices[1][1], trapezoidalPrismVertices[1][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(trapezoidalPrismVertices[0][0], trapezoidalPrismVertices[0][1], trapezoidalPrismVertices[0][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(trapezoidalPrismVertices[3][0], trapezoidalPrismVertices[3][1], trapezoidalPrismVertices[3][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(trapezoidalPrismVertices[7][0], trapezoidalPrismVertices[7][1], trapezoidalPrismVertices[7][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(trapezoidalPrismVertices[4][0], trapezoidalPrismVertices[4][1], trapezoidalPrismVertices[4][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(trapezoidalPrismVertices[4][0], trapezoidalPrismVertices[4][1], trapezoidalPrismVertices[4][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(trapezoidalPrismVertices[7][0], trapezoidalPrismVertices[7][1], trapezoidalPrismVertices[7][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(trapezoidalPrismVertices[6][0], trapezoidalPrismVertices[6][1], trapezoidalPrismVertices[6][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(trapezoidalPrismVertices[5][0], trapezoidalPrismVertices[5][1], trapezoidalPrismVertices[5][2]);
    glEnd();
}

// 根据已生成的顶点渲染长方体
// 需先调用 GenerateCuboid 填充 cuboidVertices
void RenderCuboid() {
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(cuboidVertices[0][0], cuboidVertices[0][1], cuboidVertices[0][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(cuboidVertices[1][0], cuboidVertices[1][1], cuboidVertices[1][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(cuboidVertices[2][0], cuboidVertices[2][1], cuboidVertices[2][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(cuboidVertices[3][0], cuboidVertices[3][1], cuboidVertices[3][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(cuboidVertices[1][0], cuboidVertices[1][1], cuboidVertices[1][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(cuboidVertices[0][0], cuboidVertices[0][1], cuboidVertices[0][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(cuboidVertices[4][0], cuboidVertices[4][1], cuboidVertices[4][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(cuboidVertices[5][0], cuboidVertices[5][1], cuboidVertices[5][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(cuboidVertices[7][0], cuboidVertices[7][1], cuboidVertices[7][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(cuboidVertices[6][0], cuboidVertices[6][1], cuboidVertices[6][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(cuboidVertices[2][0], cuboidVertices[2][1], cuboidVertices[2][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(cuboidVertices[3][0], cuboidVertices[3][1], cuboidVertices[3][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(cuboidVertices[5][0], cuboidVertices[5][1], cuboidVertices[5][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(cuboidVertices[6][0], cuboidVertices[6][1], cuboidVertices[6][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(cuboidVertices[2][0], cuboidVertices[2][1], cuboidVertices[2][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(cuboidVertices[1][0], cuboidVertices[1][1], cuboidVertices[1][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(cuboidVertices[0][0], cuboidVertices[0][1], cuboidVertices[0][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(cuboidVertices[3][0], cuboidVertices[3][1], cuboidVertices[3][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(cuboidVertices[7][0], cuboidVertices[7][1], cuboidVertices[7][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(cuboidVertices[4][0], cuboidVertices[4][1], cuboidVertices[4][2]);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(cuboidVertices[4][0], cuboidVertices[4][1], cuboidVertices[4][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(cuboidVertices[7][0], cuboidVertices[7][1], cuboidVertices[7][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(cuboidVertices[6][0], cuboidVertices[6][1], cuboidVertices[6][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(cuboidVertices[5][0], cuboidVertices[5][1], cuboidVertices[5][2]);
    glEnd();
}

// 生成平行四边形柱体的顶点（底面为 x-y 平面上的平行四边形）
void GenerateParallelogramPrism(double x1, double y1, double x2, double y2,
    double x3, double y3, double x4, double y4,
    double zBase, double height) {
    parallelogramPrismVertices[0][0] = x1;
    parallelogramPrismVertices[0][1] = y1;
    parallelogramPrismVertices[0][2] = zBase;

    parallelogramPrismVertices[1][0] = x2;
    parallelogramPrismVertices[1][1] = y2;
    parallelogramPrismVertices[1][2] = zBase;

    parallelogramPrismVertices[2][0] = x3;
    parallelogramPrismVertices[2][1] = y3;
    parallelogramPrismVertices[2][2] = zBase;

    parallelogramPrismVertices[3][0] = x4;
    parallelogramPrismVertices[3][1] = y4;
    parallelogramPrismVertices[3][2] = zBase;

    for (int i = 0; i < 4; i++) {
        parallelogramPrismVertices[i + 4][0] = parallelogramPrismVertices[i][0];
        parallelogramPrismVertices[i + 4][1] = parallelogramPrismVertices[i][1];
        parallelogramPrismVertices[i + 4][2] = parallelogramPrismVertices[i][2] + height;
    }
}

// 根据已生成的顶点渲染平行四边形柱体
// 需先调用 GenerateParallelogramPrism 填充 ParallelogramPrism
void RenderParallelogramPrism() {
    // 绘制底面
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(parallelogramPrismVertices[0][0], parallelogramPrismVertices[0][1], parallelogramPrismVertices[0][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(parallelogramPrismVertices[1][0], parallelogramPrismVertices[1][1], parallelogramPrismVertices[1][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(parallelogramPrismVertices[2][0], parallelogramPrismVertices[2][1], parallelogramPrismVertices[2][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(parallelogramPrismVertices[3][0], parallelogramPrismVertices[3][1], parallelogramPrismVertices[3][2]);
    glEnd();

    // 绘制顶面
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(parallelogramPrismVertices[4][0], parallelogramPrismVertices[4][1], parallelogramPrismVertices[4][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(parallelogramPrismVertices[5][0], parallelogramPrismVertices[5][1], parallelogramPrismVertices[5][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(parallelogramPrismVertices[6][0], parallelogramPrismVertices[6][1], parallelogramPrismVertices[6][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(parallelogramPrismVertices[7][0], parallelogramPrismVertices[7][1], parallelogramPrismVertices[7][2]);
    glEnd();

    // 绘制侧面
    glBegin(GL_POLYGON);
    //计算侧面法线
    double nx1 = parallelogramPrismVertices[1][1] - parallelogramPrismVertices[0][1];
    double ny1 = -(parallelogramPrismVertices[1][0] - parallelogramPrismVertices[0][0]);
    double length1 = sqrt(nx1 * nx1 + ny1 * ny1);
    if (length1 > 0) {
        nx1 /= length1;
        ny1 /= length1;
    }
    glNormal3f(nx1, ny1, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(parallelogramPrismVertices[0][0], parallelogramPrismVertices[0][1], parallelogramPrismVertices[0][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(parallelogramPrismVertices[1][0], parallelogramPrismVertices[1][1], parallelogramPrismVertices[1][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(parallelogramPrismVertices[5][0], parallelogramPrismVertices[5][1], parallelogramPrismVertices[5][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(parallelogramPrismVertices[4][0], parallelogramPrismVertices[4][1], parallelogramPrismVertices[4][2]);
    glEnd();

    // 侧面2
    glBegin(GL_POLYGON);
    double nx2 = parallelogramPrismVertices[2][1] - parallelogramPrismVertices[1][1];
    double ny2 = -(parallelogramPrismVertices[2][0] - parallelogramPrismVertices[1][0]);
    double length2 = sqrt(nx2 * nx2 + ny2 * ny2);
    if (length2 > 0) {
        nx2 /= length2;
        ny2 /= length2;
    }
    glNormal3f(nx2, ny2, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(parallelogramPrismVertices[1][0], parallelogramPrismVertices[1][1], parallelogramPrismVertices[1][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(parallelogramPrismVertices[2][0], parallelogramPrismVertices[2][1], parallelogramPrismVertices[2][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(parallelogramPrismVertices[6][0], parallelogramPrismVertices[6][1], parallelogramPrismVertices[6][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(parallelogramPrismVertices[5][0], parallelogramPrismVertices[5][1], parallelogramPrismVertices[5][2]);
    glEnd();

    // 侧面3
    glBegin(GL_POLYGON);
    double nx3 = parallelogramPrismVertices[3][1] - parallelogramPrismVertices[2][1];
    double ny3 = -(parallelogramPrismVertices[3][0] - parallelogramPrismVertices[2][0]);
    double length3 = sqrt(nx3 * nx3 + ny3 * ny3);
    if (length3 > 0) {
        nx3 /= length3;
        ny3 /= length3;
    }
    glNormal3f(nx3, ny3, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(parallelogramPrismVertices[2][0], parallelogramPrismVertices[2][1], parallelogramPrismVertices[2][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(parallelogramPrismVertices[3][0], parallelogramPrismVertices[3][1], parallelogramPrismVertices[3][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(parallelogramPrismVertices[7][0], parallelogramPrismVertices[7][1], parallelogramPrismVertices[7][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(parallelogramPrismVertices[6][0], parallelogramPrismVertices[6][1], parallelogramPrismVertices[6][2]);
    glEnd();

    // 侧面4
    glBegin(GL_POLYGON);
    double nx4 = parallelogramPrismVertices[0][1] - parallelogramPrismVertices[3][1];
    double ny4 = -(parallelogramPrismVertices[0][0] - parallelogramPrismVertices[3][0]);
    double length4 = sqrt(nx4 * nx4 + ny4 * ny4);
    if (length4 > 0) {
        nx4 /= length4;
        ny4 /= length4;
    }
    glNormal3f(nx4, ny4, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(parallelogramPrismVertices[3][0], parallelogramPrismVertices[3][1], parallelogramPrismVertices[3][2]);
    glTexCoord2f(1.0, 0.0); glVertex3f(parallelogramPrismVertices[0][0], parallelogramPrismVertices[0][1], parallelogramPrismVertices[0][2]);
    glTexCoord2f(1.0, 1.0); glVertex3f(parallelogramPrismVertices[4][0], parallelogramPrismVertices[4][1], parallelogramPrismVertices[4][2]);
    glTexCoord2f(0.0, 1.0); glVertex3f(parallelogramPrismVertices[7][0], parallelogramPrismVertices[7][1], parallelogramPrismVertices[7][2]);
    glEnd();
}
// 生成三角柱的顶点（底面为 x-y 平面上的三角形）
// x1, y1, x2, y2, x3, y3：底面三角形三个顶点；zBase：底面z坐标；height：柱体高度
void GenerateTriangularPrism(double x1, double y1, double x2, double y2, double x3, double y3, double zBase, double height) {
    // 底面
    triangularPrismVertices[0][0] = x1;
    triangularPrismVertices[0][1] = y1;
    triangularPrismVertices[0][2] = zBase;

    triangularPrismVertices[1][0] = x2;
    triangularPrismVertices[1][1] = y2;
    triangularPrismVertices[1][2] = zBase;

    triangularPrismVertices[2][0] = x3;
    triangularPrismVertices[2][1] = y3;
    triangularPrismVertices[2][2] = zBase;

    // 顶面（z 方向平移）
    for (int i = 0; i < 3; i++) {
        triangularPrismVertices[i + 3][0] = triangularPrismVertices[i][0];
        triangularPrismVertices[i + 3][1] = triangularPrismVertices[i][1];
        triangularPrismVertices[i + 3][2] = triangularPrismVertices[i][2] + height;
    }
}

// 根据已生成的顶点渲染三角柱
// 需先调用 GeneratetriangularPrism 填充 triangularPrism
void RenderTriangularPrism() {
    // 绘制底面三角形
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, -1.0);  // 底面法线向下
    glTexCoord2f(0.0, 0.0);
    glVertex3f(triangularPrismVertices[0][0], triangularPrismVertices[0][1], triangularPrismVertices[0][2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(triangularPrismVertices[1][0], triangularPrismVertices[1][1], triangularPrismVertices[1][2]);
    glTexCoord2f(0.5, 1.0);
    glVertex3f(triangularPrismVertices[2][0], triangularPrismVertices[2][1], triangularPrismVertices[2][2]);
    glEnd();

    // 绘制顶面三角形
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, 1.0);  // 顶面法线向上
    glTexCoord2f(0.0, 0.0);
    glVertex3f(triangularPrismVertices[3][0], triangularPrismVertices[3][1], triangularPrismVertices[3][2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(triangularPrismVertices[4][0], triangularPrismVertices[4][1], triangularPrismVertices[4][2]);
    glTexCoord2f(0.5, 1.0);
    glVertex3f(triangularPrismVertices[5][0], triangularPrismVertices[5][1], triangularPrismVertices[5][2]);
    glEnd();

    // 绘制侧面1（连接点1-2）
    glBegin(GL_QUADS);
    // 计算侧面1的法线
    double nx1 = triangularPrismVertices[1][1] - triangularPrismVertices[0][1];
    double ny1 = -(triangularPrismVertices[1][0] - triangularPrismVertices[0][0]);
    double length1 = sqrt(nx1 * nx1 + ny1 * ny1);
    if (length1 > 0) {
        nx1 /= length1;
        ny1 /= length1;
    }
    glNormal3f(nx1, ny1, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(triangularPrismVertices[0][0], triangularPrismVertices[0][1], triangularPrismVertices[0][2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(triangularPrismVertices[1][0], triangularPrismVertices[1][1], triangularPrismVertices[1][2]);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(triangularPrismVertices[4][0], triangularPrismVertices[4][1], triangularPrismVertices[4][2]);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(triangularPrismVertices[3][0], triangularPrismVertices[3][1], triangularPrismVertices[3][2]);
    glEnd();

    // 绘制侧面2（连接点2-3）
    glBegin(GL_QUADS);
    // 计算侧面2的法线
    double nx2 = triangularPrismVertices[2][1] - triangularPrismVertices[1][1];
    double ny2 = -(triangularPrismVertices[2][0] - triangularPrismVertices[1][0]);
    double length2 = sqrt(nx2 * nx2 + ny2 * ny2);
    if (length2 > 0) {
        nx2 /= length2;
        ny2 /= length2;
    }
    glNormal3f(nx2, ny2, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(triangularPrismVertices[1][0], triangularPrismVertices[1][1], triangularPrismVertices[1][2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(triangularPrismVertices[2][0], triangularPrismVertices[2][1], triangularPrismVertices[2][2]);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(triangularPrismVertices[5][0], triangularPrismVertices[5][1], triangularPrismVertices[5][2]);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(triangularPrismVertices[4][0], triangularPrismVertices[4][1], triangularPrismVertices[4][2]);
    glEnd();

    // 绘制侧面3（连接点3-1）
    glBegin(GL_QUADS);
    // 计算侧面3的法线
    double nx3 = triangularPrismVertices[0][1] - triangularPrismVertices[2][1];
    double ny3 = -(triangularPrismVertices[0][0] - triangularPrismVertices[2][0]);
    double length3 = sqrt(nx3 * nx3 + ny3 * ny3);
    if (length3 > 0) {
        nx3 /= length3;
        ny3 /= length3;
    }
    glNormal3f(nx3, ny3, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(triangularPrismVertices[2][0], triangularPrismVertices[2][1], triangularPrismVertices[2][2]);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(triangularPrismVertices[0][0], triangularPrismVertices[0][1], triangularPrismVertices[0][2]);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(triangularPrismVertices[3][0], triangularPrismVertices[3][1], triangularPrismVertices[3][2]);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(triangularPrismVertices[5][0], triangularPrismVertices[5][1], triangularPrismVertices[5][2]);
    glEnd();
}

