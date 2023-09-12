#include <cstddef>
#include <cstdint>
#include "window.hpp"
#include "debug.hpp"

using namespace JRE;

WindowManager::WindowManager (uint32_t x, uint32_t y)
    : main_window (window_t{ x, y, "JRE", nullptr })
{
  /* Initialize the library */
  glfwInit ();

  glfwWindowHint (GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint (GLFW_SAMPLES, 16);

  /* Create a windowed mode window and its OpenGL context */
  main_window.app
      = glfwCreateWindow (main_window.width, main_window.height,
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

  glDebugMessageCallback (MessageCallback, &debug_params);
#else
  glEnable (GL_DEBUG_OUTPUT);

  debug_params_t *debug_params = new debug_params_t ();
  debug_params->throw_error = false;

  glDebugMessageCallback (MessageCallback, &debug_params);
#endif

  glfwSwapInterval (1);
  glEnable (GL_MULTISAMPLE);
  glEnable (GL_DEPTH_TEST);

  glfwSetKeyCallback (main_window.app, nullptr);
}

uint32_t
WindowManager::start ()
{
  while (!glfwWindowShouldClose (main_window.app))
    {
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      int width, height;
      glfwGetWindowSize (main_window.app, &width, &height);
      glViewport (0, 0, width, height);

      /* Render here */

      /* Swap front and back buffers */
      glfwSwapBuffers (main_window.app);

      /* Poll for and process events */
      glfwPollEvents ();
    }

  glfwTerminate ();

  return 0;
}
