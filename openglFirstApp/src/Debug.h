#pragma once
#ifdef _DEBUG
#define GLCALL(x) x;\
   // if (error) {__debugbreak();error = false;};
#else
#define GLCALL(x) x;
#endif // _DEBUG


//#define GLM_FORCE_DEPTH_ZERO_TO_ONE 1;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static bool error = false;

inline void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		error = true;
	}
	std::cout << "[OpenGL Error](" << type << " : Severity: " << severity << ") " << message << std::endl;
}

inline void test_window_creation(GLFWwindow* wind) {

	if (!wind)
	{
		glfwTerminate();
		exit(-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(wind);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
}