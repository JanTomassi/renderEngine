#include "debug.hpp"
#include <stdexcept>

void GLAPIENTRY
MessageCallback (GLenum source, GLenum type, GLuint id, GLenum severity,
                 GLsizei length, const GLchar *message, const void *userParam)
{
  std::string severity_string;
  std::string type_string;
  switch (severity)
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
    }
  switch (type)
    {
    case (GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR):
      type_string = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
      break;
    case (GL_DEBUG_TYPE_ERROR):
      type_string = "GL_DEBUG_TYPE_ERROR";
      break;
    case ((int)GL_DEBUG_TYPE_OTHER):
      type_string = "GL_DEBUG_TYPE_OTHER";
      break;
    case ((int)GL_DEBUG_TYPE_PERFORMANCE):
      type_string = "GL_DEBUG_TYPE_PERFORMANCE";
      break;
    default:
      type_string = std::to_string (type);
      break;
    }
  if(((debug_params_t*)userParam)->throw_error){
    throw std::runtime_error("Error on opengl call");
  }
  std::cout << "[OpenGL Error](" << type << " : Severity: " << severity_string
            << ") " << message << std::endl;
}

void
test_window_creation (GLFWwindow *wind)
{
  if (!wind)
    {
      glfwTerminate ();
      exit (-1);
    }

  /* Make the window's context current */
  glfwMakeContextCurrent (wind);

  std::cout << glGetString (GL_VERSION) << std::endl;
}
