#pragma once
#include <vector>
#include <GLFW/glfw3.h>

class Input
{
public:
	Input(){};
	Input(Input* in);
	virtual void keyfun(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
	virtual void mousefun(GLFWwindow* window, int xpos, int ypos) = 0;
};

