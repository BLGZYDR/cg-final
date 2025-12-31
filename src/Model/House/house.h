#ifndef HOUSE_H
#define HOUSE_H

// #include <glad/gl.h>

// OpenGL 固定管线 API
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

// 房子绘制函数
void drawHouse();

#endif