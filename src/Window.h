#pragma once
#include <string>
#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"

class Window
{
private:
	int dim_width;
	int dim_hight;
	GLFWwindow* app;
	Scene* scene;


	InputManager& inputManager = InputManager::getInstance();
	Camera* cam;

public:
	Window(int x, int y);
	void LoadScene(std::vector<std::string> filepaths);
	void start();
};

