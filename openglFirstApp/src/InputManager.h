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

	// Static callback funcion for glfw c interface for the keyboard movement
	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		//here we access the instance via the singleton pattern and forward the callback to the instance method
		getInstance().keyboardCallbackImp(window, key, scancode, action, mods);
	}
	// Static callback funcion for glfw c interface for the mouse movement
	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos) 
	{
		//here we access the instance via the singleton pattern and forward the callback to the instance method
		getInstance().mousePosCallbackImp(window, xpos, ypos);
	}

	//this is the implementascion of the callback method
	void keyboardCallbackImp(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		for (auto& input : inputs)
		{
			input->keyfun(window, key, scancode, action, mods);
		}
	}
	//this is the implementascion of the callback method
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
