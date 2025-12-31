#ifndef HEADERS_H
#define HEADERS_H

// GLFW + ImGui + Glm
// #include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// OpenGL 固定管线 API
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

// 原有标准库文件
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using std::cout;
using std::vector;

// ===== 图形学数据结构（全局可访问）=====
// 像素结构体：存储像素坐标、深度值和颜色（软件光栅化可选使用）
struct Fragment {
    int x, y;               // 像素屏幕坐标
    float depth;            // 深度值（用于深度测试，判断遮挡关系）
    glm::vec3 color;        // 像素RGB颜色
};

// 顶点结构体：包含顶点位置 + 顶点法向量（核心几何顶点数据）
struct Vertex {
    glm::vec3 position;     // 顶点三维空间坐标
    glm::vec3 normal;       // 顶点法向量（用于光照计算）
    glm::vec2 texCoord;     // 纹理坐标（u, v）
};

// 三角形索引结构体：存储Mesh顶点列表的索引，实现顶点复用
struct Triangle {
    int v[3];               // 对应Mesh::vertices的3个顶点索引（按逆时针顺序存储，便于背面剔除）
};

// 立体图形网格结构体：统一封装顶点数据和三角形索引，一个Mesh对应一个完整3D图形
struct Mesh {
    vector<Vertex> vertices;        // 顶点列表（存储所有唯一顶点）
    vector<Triangle> triangles;     // 三角形索引列表（存储所有三角化后的索引）
};
// ==============================================

// 外部窗口宽高变量声明
extern GLfloat w;
extern GLfloat h;

// 颜色定义
#define WHITE      1.0, 1.0, 1.0
#define GREEN      0.0, 0.502, 0.0
#define RED        0.6, 0.1, 0.1
#define DARK_RED    0.6, 0.078, 0.235
#define GRAY       0.502, 0.502, 0.502
#define HGRAY      0.117, 0.180, 0.227
#define BLUE       0.0, 0.0, 1.0
#define GOLD       1.0, 215.0/255.0, 0.0
#define HGREEN     0.0, 100.0/255.0, 0.0
#define BROWN      73/255.0, 57/255.0, 45/255.0
#define MEN        244.0/255.0, 164.0/255.0, 96.0/255.0
#define MENBA      139.0/255.0, 69.0/255.0, 19.0/255.0
#define DARK_GREEN 0.0, 0.4, 0.0     
#define FOREST_GREEN 0.133, 0.545, 0.133  
#define WATER_BLUE 0.0, 0.5, 1.0     

#define PI 3.14159265f

#endif
