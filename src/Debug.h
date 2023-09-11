#pragma once
#ifdef _DEBUG
#define GLCALL(x)                                                             \
  x;                                                                          \
  if (error)                                                                  \
    {                                                                         \
      __debugbreak ();                                                        \
      error = false;                                                          \
    };
#else
#define GLCALL(x) x;
#endif // _DEBUG

// #define GLM_FORCE_DEPTH_ZERO_TO_ONE 1;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

static bool error = false;

inline void GLAPIENTRY
MessageCallback (GLenum source, GLenum type, GLuint id, GLenum severity,
                 GLsizei length, const GLchar *message, const void *userParam)
{
  if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
    {
      error = true;
    }
  std::string severity_string;
  switch (type)
    {
    case ((int)GL_DEBUG_SEVERITY_NOTIFICATION):
      severity_string = "GL_DEBUG_SEVERITY_NOTIFICATION";
      break;
    case ((int)GL_DEBUG_SEVERITY_LOW):
      severity_string = "GL_DEBUG_SEVERITY_LOW";
      break;
    case ((int)GL_DEBUG_SEVERITY_MEDIUM):
      severity_string = "GL_DEBUG_SEVERITY_MEDIUM";
      break;
    case ((int)GL_DEBUG_SEVERITY_HIGH):
      severity_string = "GL_DEBUG_SEVERITY_HIGH";
      break;
    case ((int)GL_DEBUG_TYPE_OTHER):
      severity_string = "GL_DEBUG_TYPE_OTHER";
      break;
    case ((int)GL_DEBUG_TYPE_PERFORMANCE):
      severity_string = "GL_DEBUG_TYPE_PERFORMANCE";
      break;
    default:
      severity_string = std::to_string (severity);
      break;
    }
  std::cout << "[OpenGL Error](" << type << " : Severity: " << severity_string
            << ") " << message << std::endl;
}

inline void
test_window_creation (GLFWwindow *wind)
{

  if (!wind)
    {
      glfwTerminate ();
      exit (-1);
    }

  /* Make the window's context current */
  glfwMakeContextCurrent (wind);

  if (glewInit () != GLEW_OK)
    std::cout << "Error!" << std::endl;

  std::cout << glGetString (GL_VERSION) << std::endl;
}