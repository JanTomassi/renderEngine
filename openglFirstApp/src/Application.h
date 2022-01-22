#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <assert.h>
#include "shader.h"

#define GLCALL(x) x;\
    if (error) {__debugbreak();error = false;};

bool error = false;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		error = true;
	}
	std::cout << "[OpenGL Error](" << type << " : Severity: " << severity << ") " << message << std::endl;
}

void test_window_creation(GLFWwindow* wind) {

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