#pragma once
#include <csignal>
#ifdef _DEBUG
#define GLCALL(x)                                                             \
  {                                                                           \
    x;                                                                        \
    if (error)                                                                \
      {                                                                       \
        std::signal (SIGTRAP);                                                \
        error = false;                                                        \
      };
#else
#define GLCALL(x) x;
#endif // _DEBUG

// #define GLM_FORCE_DEPTH_ZERO_TO_ONE 1;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

extern bool error;

extern void GLAPIENTRY MessageCallback (GLenum source, GLenum type, GLuint id,
                                        GLenum severity, GLsizei length,
                                        const GLchar *message,
                                        const void *userParam);

extern void test_window_creation (GLFWwindow *wind);
