#ifndef SCENE_H
#define SCENE_H

// OpenGL 固定管线 API
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

extern GLfloat w;
extern GLfloat h;
extern double rotate_x;
extern double rotate_y;

void display(void);

#endif