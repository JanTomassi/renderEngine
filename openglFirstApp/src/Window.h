#pragma once
#include <string>
#include "Scene.h"
class Window
{
private:
	int dim_width;
	int dim_hight;
	GLFWwindow* app;
	Scene* scene;
public:
	Window(int x, int y);
	void LoadScene(std::vector<std::string> filepaths);
	void start();
};

