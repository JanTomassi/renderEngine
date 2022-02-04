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

shader* base_shader;

Window::Window(int x, int y) : dim_width(x), dim_hight(y)
{
	/* Initialize the library */
	GLCALL(glfwInit());

	GLCALL(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE));
	glfwWindowHint(GLFW_SAMPLES, 16);

	/* Create a windowed mode window and its OpenGL context */
	app = GLCALL(glfwCreateWindow(dim_width, dim_hight, "Hello World", NULL, NULL));

	GLCALL(test_window_creation(app));
	scene = new Scene(app);

	glfwSwapInterval(1);
	glEnable(GL_MULTISAMPLE);
	GLCALL(glEnable(GL_DEPTH_TEST));

#ifdef GLCALL	// Enable debug output
	GLCALL(glEnable(GL_DEBUG_OUTPUT));
	GLCALL(glDebugMessageCallback(MessageCallback, 0));
#endif// GLCALL
	std::vector<std::string> mesh;
	//mesh.push_back("C:\\Users\\jangi\\Desktop\\plane.obj");
	mesh.push_back("C:\\Users\\jangi\\Desktop\\face.obj");
	scene->loadsAsync(mesh);


	base_shader = new shader();
	//base_shader->add(GL_COMPUTE_SHADER, );
	base_shader->add(GL_VERTEX_SHADER, "C:/Users/jangi/source/repos/app/openglFirstApp/shader/VertexShader.shader");
	//base_shader->add(GL_GEOMETRY_SHADER, "C:/Users/jangi/source/repos/app/openglFirstApp/shader/GeometryShader.shader");
	base_shader->add(GL_FRAGMENT_SHADER, "C:/Users/jangi/source/repos/app/openglFirstApp/shader/FragmentShader.shader");
	base_shader->compile();
	base_shader->useShader();

	glm::mat4 proj = glm::perspective(glm::radians(64.0f), (GLfloat)dim_width / (GLfloat)dim_hight, (float)std::pow(2, -10), 10000.0f);

	//proj = glm::ortho(-1.0, 1.0,
	//	-(double)dim_hight / dim_width, (double)dim_hight / dim_width,
	//	(double)std::pow(2, -10), 1000.0);

	glm::mat4 tanslate(1.0);
	tanslate = glm::translate(tanslate, glm::vec3(0.0, 0.0, -1.5f));
	tanslate = glm::rotate(tanslate, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	base_shader->SetUniformMat4f("m_porj", proj);
	base_shader->SetUniformMat4f("m_tran", tanslate);
}

void Window::start()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(app))
	{
		int width, height;
		glfwGetWindowSize(app, &width, &height);
		glViewport(0, 0, width, height);

		/* Render here */
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 proj = glm::perspective(glm::radians(64.0f), (GLfloat)width / (GLfloat)height, (float)std::pow(2, -10), 10000.0f);

		glm::mat4 tanslate(1.0f);
		tanslate = glm::translate(tanslate, glm::vec3(0.0, 0.0, -1.5));
		glm::vec3 dir_vec = glm::normalize(glm::vec3(0.0, glm::sin((float)glfwGetTime()/4), glm::sin((float)glfwGetTime() / 8) / 8));
		tanslate = glm::rotate(tanslate, (float)glfwGetTime(), dir_vec);

		base_shader->SetUniformMat4f("m_porj", proj);
		base_shader->SetUniformMat4f("m_tran", tanslate);

		scene->render();

		/* Swap front and back buffers */
		GLCALL(glfwSwapBuffers(app));

		/* Poll for and process events */
		GLCALL(glfwPollEvents());

	}

	GLCALL(glfwTerminate());
}
