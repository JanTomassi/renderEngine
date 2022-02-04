#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "InputManager.h"

class Camera : public Input
{
private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	bool firstMouse = true;
	bool mouse_state = true;
	float lastX = 0, lastY = 0;
	float yaw = 0, pitch = 0;

public:
	Camera();
	~Camera() = default;

	// Inherited via Input
	void keyfun(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	void reCalculateView() {
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	glm::mat4 viewMatrix() {
		return view;
	}

	// Inherited via Input
	virtual void mousefun(GLFWwindow* window, int xpos, int ypos) override;
};

