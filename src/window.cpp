#include "window.hpp"
#include "debug.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "GLFW/glfw3.h"
#include "mesh.hpp"
#include "shader.hpp"

using namespace JRE;

WindowManager::WindowManager (uint32_t x, uint32_t y)
    : main_window (window_t{ x, y, "JRE", nullptr })
{
  /* Initialize the library */
  if (!glfwInit ())
    exit (-1);

  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint (GLFW_RESIZABLE, GLFW_FALSE);

#ifdef DEBUG
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#else
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  glfwWindowHint (GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint (GLFW_SAMPLES, 16);

  /* Create a windowed mode window and its OpenGL context */
  main_window.app
      = glfwCreateWindow (static_cast<int> (main_window.width),
                          static_cast<int> (main_window.height),
                          main_window.window_name.c_str (), NULL, NULL);

  test_window_creation (main_window.app);

  if (glewInit () != GLEW_OK)
    {
      std::cout << "glew Init fail!" << std::endl;
      exit (-1);
    }

#ifdef DEBUG
  glEnable (GL_DEBUG_OUTPUT);
  glEnable (GL_DEBUG_OUTPUT_SYNCHRONOUS);

  debug_params_t *debug_params = new debug_params_t ();
  debug_params->throw_error = true;

  glDebugMessageCallback (MessageCallback, debug_params);
#else
  glEnable (GL_DEBUG_OUTPUT);

  debug_params_t *debug_params = new debug_params_t ();
  debug_params->throw_error = false;

  glDebugMessageCallback (MessageCallback, debug_params);
#endif

  glfwSwapInterval (1);
  glEnable (GL_MULTISAMPLE);
  glEnable (GL_DEPTH_TEST);

  glfwSetKeyCallback (main_window.app, nullptr);
}

void    
WindowManager::start ()
{
  glObject::Shader shader;
  shader.add_src (GL_VERTEX_SHADER, "./shader/vertex.shader");
  shader.add_src (GL_FRAGMENT_SHADER, "./shader/fragment.shader");
  shader.use_program();
  auto [va, info] = Mesh::load_mesh ("./object/moke.obj");
  while (!glfwWindowShouldClose (main_window.app))
    {
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      int width, height;
      glfwGetWindowSize (main_window.app, &width, &height);
      glViewport (0, 0, width, height);

      /* Render here */
      va.bind ();
      glDrawElements (GL_TRIANGLES, static_cast<int>(info.idx.size ()), GL_UNSIGNED_INT,
                      info.idx.data ());

      /* Swap front and back buffers */
      glfwSwapBuffers (main_window.app);

      /* Poll for and process events */
      glfwPollEvents ();
    }

  glfwTerminate ();
}
