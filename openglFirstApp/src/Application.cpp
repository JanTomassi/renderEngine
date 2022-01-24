#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>
#include <assert.h>
#include <fstream>
#include <mutex>
#include <vector>
#include <future>

#include "shader.h"
#include "object.h"
#include "Application.h"

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

std::mutex meshMutex;

static void LoadMesh(std::vector<object::c_object>* mesh, std::string filepath) {
	auto obj = object::c_object(filepath);

	std::lock_guard<std::mutex> lock(meshMutex);
	mesh->push_back(std::ref(obj));
}

int main(void)
{
	unsigned int dim_width = 640;
	unsigned int dim_hight = 480;

	GLFWwindow* window;
	/* Initialize the library */
	GLCALL(glfwInit());

	GLCALL(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE));
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = GLCALL(glfwCreateWindow(dim_width, dim_hight, "Hello World", NULL, NULL));

	GLCALL(test_window_creation(window));

	glfwSwapInterval(1);
	GLCALL(glEnable(GL_DEPTH_TEST));

	// Enable debug output
	GLCALL(glEnable(GL_DEBUG_OUTPUT));
	GLCALL(glDebugMessageCallback(MessageCallback, 0));

	object::c_object obj = object::c_object("C:\\Users\\jangi\\Desktop\\face.obj");

	shader base_shader = shader(vs, fs);
	base_shader.useShader();

	glm::mat4 proj = glm::perspective(glm::radians(64.0f), (GLfloat)dim_width / (GLfloat)dim_hight, (float)std::pow(2,-10), 10000.0f);
	base_shader.SetUniformMat4f("m_porj", proj);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		obj.render();

		/* Swap front and back buffers */

		GLCALL(glfwSwapBuffers(window));

		/* Poll for and process events */
		GLCALL(glfwPollEvents());
	}

	GLCALL(glfwTerminate());
	return 0;
}