#include "debug.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

void GLAPIENTRY
MessageCallback (GLenum source, GLenum type, [[maybe_unused]] GLuint id,
                 GLenum severity, [[maybe_unused]] GLsizei length,
                 const GLchar *message, const void *userParam)
{
  std::string source_string;
  std::string type_string;
  std::string severity_string;
  std::string color;
  bool is_throwing = true;
  switch (source)
    {
    case GL_DEBUG_SOURCE_API:
      source_string = "Source: API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      source_string = "Source: Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      source_string = "Source: Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      source_string = "Source: Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      source_string = "Source: Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      source_string = "Source: Other";
      break;
    }
  switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
      type_string = "Type: Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      type_string = "Type: Deprecated Behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      type_string = "Type: Undefined Behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      type_string = "Type: Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      type_string = "Type: Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      type_string = "Type: Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      type_string = "Type: Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      type_string = "Type: Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      type_string = "Type: Other";
      break;
    }
  switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
      severity_string = "Severity: high";
      color = "\033[31m";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      severity_string = "Severity: medium";
      color = "\033[103m";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      severity_string = "Severity: low";
      color = "\033[32m";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      severity_string = "Severity: notification";
      color = "\033[0m";
      is_throwing = false;
      break;
    }
  if (((debug_params_t *)userParam)->throw_error && is_throwing)
    {
      std::stringstream out;
      out << "[OpenGL Error](" << source_string << "; " << type_string << "; "
          << severity_string << ") " << message << std::endl;
      throw std::runtime_error (out.str ());
    }
  else
    {
      std::cout << color << "[OpenGL Error](" << source_string << "; "
                << type_string << "; " << severity_string << ") " << message
                << "\033[0m" << std::endl;
    }
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
