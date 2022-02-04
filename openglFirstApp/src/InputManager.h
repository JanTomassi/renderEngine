#pragma once
#include <vector>
#include <iostream>
#include "Input.h"

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;
	void call(GLFWwindow* window, int key, int scancode, int action, int mods);
	void add(Input* in);

	static InputManager& getInstance() // Singleton is accessed via getInstance()
	{
		static InputManager instance; // lazy singleton, instantiated on first use
		return instance;
	}

	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) // this method is specified as glfw callback
	{
		//here we access the instance via the singleton pattern and forward the callback to the instance method
		getInstance().keyboardCallbackImp(window, key, scancode, action, mods);
	}
	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos) // this method is specified as glfw callback
	{
		//here we access the instance via the singleton pattern and forward the callback to the instance method
		getInstance().mousePosCallbackImp(window, xpos, ypos);
	}

	void keyboardCallbackImp(GLFWwindow* window, int key, int scancode, int action, int mods) //this is the actual implementation of the callback method
	{
		for (auto& input : inputs)
		{
			input->keyfun(window, key, scancode, action, mods);
		}
	}
	void mousePosCallbackImp(GLFWwindow* window, double xpos, double ypos) //this is the actual implementation of the callback method
	{
		for (auto& input : inputs)
		{
			input->mousefun(window, xpos, ypos);
		}
	}

	InputManager(InputManager const&) = default; // prevent copies
	void operator=(InputManager const&); // prevent assignments
private:
	std::vector<Input*> inputs;

};
