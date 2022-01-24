#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>
#include <assert.h>
#include "Debug.h"
#include "Mesh.h"
#include "shader.h"

std::string vs = R"glsl(
		#version 460
		layout(location = 0) in vec4 position;
		layout(location = 1) in vec4 m_normal;
		layout(location = 0) out vec4 normal;

		uniform mat4 m_porj;

		void main(){
			gl_Position = m_porj * position;
			normal = m_normal;
		}
		)glsl";
std::string fs = R"glsl(
		#version 460
		layout(location = 0) out vec4 color;
		layout(location = 0) in vec4 normal;

		void main(){
			color = normal;
		}
		)glsl";

Window::Window(int x, int y) : dim_width(x), dim_hight(y)
{
	/* Initialize the library */
	GLCALL(glfwInit());

	GLCALL(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE));

	/* Create a windowed mode window and its OpenGL context */
	app = GLCALL(glfwCreateWindow(dim_width, dim_hight, "Hello World", NULL, NULL));

	GLCALL(test_window_creation(app));

	glfwSwapInterval(1);
	GLCALL(glEnable(GL_DEPTH_TEST));

#ifdef GLCALL	// Enable debug output
	GLCALL(glEnable(GL_DEBUG_OUTPUT));
	GLCALL(glDebugMessageCallback(MessageCallback, 0));
#endif// GLCALL

	scene.loadSynch("C:\\Users\\jangi\\Desktop\\face.obj");
	scene.loadSynch("C:\\Users\\jangi\\Desktop\\ncat.obj");

	shader base_shader = shader(vs, fs);
	base_shader.useShader();

	glm::mat4 proj = glm::perspective(glm::radians(64.0f), (GLfloat)dim_width / (GLfloat)dim_hight, (float)std::pow(2, -10), 10000.0f);
	base_shader.SetUniformMat4f("m_porj", proj);
}

void Window::LoadScene(std::vector<std::string> filepaths)
{
}

void Window::start()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(app))
	{
		/* Render here */
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		scene.render();

		/* Swap front and back buffers */

		GLCALL(glfwSwapBuffers(app));

		/* Poll for and process events */
		GLCALL(glfwPollEvents());
	}

	GLCALL(glfwTerminate());
}
