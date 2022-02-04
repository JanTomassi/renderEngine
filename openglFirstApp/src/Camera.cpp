#include "Camera.h"
#include <iostream>

Camera::Camera() : Input(this){};

void Camera::keyfun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	const float cameraSpeed = 0.05f;
	if (action == GLFW_REPEAT || action == GLFW_PRESS)
	{
		switch (key)
		{
		case(GLFW_KEY_W):
			cameraPos += cameraSpeed * cameraFront;
			reCalculateView();
			break;
		case(GLFW_KEY_S):
			cameraPos -= cameraSpeed * cameraFront;
			reCalculateView();
			break;
		case(GLFW_KEY_A):
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			reCalculateView();
			break;
		case(GLFW_KEY_D):
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			reCalculateView();
			break;
		case(GLFW_KEY_UP):
			cameraFront += glm::vec3(0.0, cameraSpeed, 0.0);
			reCalculateView();
			break;
		case(GLFW_KEY_DOWN):
			cameraFront += glm::vec3(0.0, -cameraSpeed, 0.0);
			reCalculateView();
			break;
		case(GLFW_KEY_LEFT):
			cameraFront += glm::vec3(-cameraSpeed, 0.0, 0.0);
			reCalculateView();
			break;
		case(GLFW_KEY_RIGHT):
			cameraFront += glm::vec3(cameraSpeed, 0.0, 0.0);
			reCalculateView();
			break;
		case(GLFW_KEY_ESCAPE):
			if (action == GLFW_PRESS) {
				mouse_state ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				mouse_state = !mouse_state;
			}
			break;
		default:
			break;
		}
	}
}

void Camera::mousefun(GLFWwindow* window, int xpos, int ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
	reCalculateView();
}
