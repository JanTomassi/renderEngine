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
#include "Global.h"
#include "Texture.h"

shader* base_shader;
shader* cs;

Window::Window(int x, int y) : dim_width(x), dim_hight(y), cam(new Camera())
{
	/* Initialize the library */
	GLCALL(glfwInit());

	GLCALL(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE));
	glfwWindowHint(GLFW_SAMPLES, 16);

	/* Create a windowed mode window and its OpenGL context */
	app = GLCALL(glfwCreateWindow(dim_width, dim_hight, "Hello World", NULL, NULL));

	GLCALL(test_window_creation(app));
	scene = new Scene(app);

	glfwSwapInterval(2);
	glEnable(GL_MULTISAMPLE);
	GLCALL(glEnable(GL_DEPTH_TEST));

	GLCALL(glfwSetKeyCallback(app, nullptr));

#ifdef GLCALL	// Enable debug output
	GLCALL(glEnable(GL_DEBUG_OUTPUT));
	GLCALL(glDebugMessageCallback(MessageCallback, 0));
#endif// GLCALL
	std::vector<std::string> mesh;
	//mesh.push_back("C:\\Users\\jangi\\Desktop\\plane.obj");
	mesh.push_back("C:\\Users\\jangi\\Desktop\\face.obj");
	scene->loadsAsync(mesh);

	cs = new shader();
	cs->add(GL_COMPUTE_SHADER, "C:/Users/jangi/source/repos/app/openglFirstApp/shader/ComputeShader.shader");
	cs->compile();
	cs->useShader();

	glfwSetKeyCallback(app, inputManager.keyboardCallback);
	glfwSetCursorPosCallback(app, inputManager.mousePosCallback);
	glfwSetInputMode(app, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::start() {
	/*Texture tex0(GL_TEXTURE_2D, 0, 0);
	tex0.Push(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	tex0.Push(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	tex0.Push(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	tex0.Push(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	tex0.setTexture();
	tex0.BindImage(GL_WRITE_ONLY);*/

	GLuint tex_output;
	glGenTextures(1, &tex_output);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_output);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 640, 480, 0, GL_RGBA, GL_FLOAT, NULL));
	GLCALL(glBindImageTexture(0, tex_output, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));

	cs->useShader();

	glm::vec3 pos(0.0, 0.0, 0.0);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(app))
	{
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		int width, height;
		glfwGetWindowSize(app, &width, &height);
		glViewport(0, 0, width, height);
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL));
		GLCALL(glBindImageTexture(0, tex_output, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));

		/* Render here */
		glm::mat4 proj = glm::infinitePerspective(glm::radians(120.0f), (GLfloat)width / (GLfloat)height, 0.1f);
		//proj = glm::inverse(proj);

		proj = cam->rot() * proj;

		cs->SetUniformMat4f("m_proj", proj);
		cs->SetUniformVet3f("camera_position", cam->pos());
		cs->SetUniformVet3f("camera_front", cam->front());
		cs->SetUniformVet2f("windowSize", glm::vec2(width, height));

		GLCALL(glDispatchCompute((GLuint)width, (GLuint)height, 1));

		// make sure writing to image has finished before read
		GLCALL(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));

		GLuint fboId = 0;
		glGenFramebuffers(1, &fboId);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fboId);

		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, tex_output, 0);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);  // If not already bound
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
			GL_COLOR_BUFFER_BIT, GL_NEAREST);

		/* Swap front and back buffers */
		GLCALL(glfwSwapBuffers(app));

		/* Poll for and process events */
		GLCALL(glfwPollEvents());
		LastTimeGlobal = glfwGetTime();
	}
	GLCALL(glfwTerminate());
}
