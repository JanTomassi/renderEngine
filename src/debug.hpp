#pragma once
#include <csignal>

// #define GLM_FORCE_DEPTH_ZERO_TO_ONE 1;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

typedef struct
{
  bool throw_error;
} debug_params_t;

extern void GLAPIENTRY MessageCallback (GLenum source, GLenum type, GLuint id,
                                        GLenum severity, GLsizei length,
                                        const GLchar *message,
                                        const void *userParam);

extern void test_window_creation (GLFWwindow *wind);
