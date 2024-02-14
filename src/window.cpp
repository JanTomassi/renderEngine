#include "window.hpp"
#include "debug.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "scene.hpp"

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

  shader.use_program ();

  Scene scene;
  int i = 0;

  scene.load_mesh_async ("./object/ico.obj");

  glm::vec3 pos = glm::vec3 (0, 1, 1);
  glm::mat4 look = glm::lookAt (pos, glm::vec3 (0, 0, 0), glm::vec3 (0, 1, 0));

  while (!glfwWindowShouldClose (main_window.app))
    {
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      int width, height;
      glfwGetWindowSize (main_window.app, &width, &height);
      glViewport (0, 0, width, height);

      /* Render here */
      glm::mat4 proj = glm::infinitePerspective (
          glm::radians (80.0f), (GLfloat)width / (GLfloat)height, 0.1f);

      glm::mat4 cam_space = proj * look;
      shader.set_uniform_mat_4f ("cam_space", cam_space);

      scene.render ();

      /* Swap front and back buffers */
      glfwSwapBuffers (main_window.app);

      /* Poll for and process events */
      glfwPollEvents ();
    }

  glfwTerminate ();
}
