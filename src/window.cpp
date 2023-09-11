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
  glDebugMessageCallback (MessageCallback, 0);
#endif

  glfwSwapInterval (1);
  glEnable (GL_MULTISAMPLE);
  GLCALL (glEnable (GL_DEPTH_TEST));

  GLCALL (glfwSetKeyCallback (main_window.app, nullptr));
}

uint32_t
WindowManager::start ()
{

  while (!glfwWindowShouldClose (main_window.app))
    {
      GLCALL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
      int width, height;
      glfwGetWindowSize (main_window.app, &width, &height);
      glViewport (0, 0, width, height);

      /* Render here */

      /* Swap front and back buffers */
      GLCALL (glfwSwapBuffers (main_window.app));

      /* Poll for and process events */
      GLCALL (glfwPollEvents ());
    }

  GLCALL (glfwTerminate ());

  return 0;
}
