/*
* Author: Dallin Carling Lovin
* Wrapper class for a GLFW window.
*/

#pragma once
#include <iostream>

#include <glfw3.h>

#include "constants.h"

class bWindow {
private:
	GLFWwindow* window;

public:
	bWindow() {
		window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH,
			DEFAULT_WINDOW_HEIGHT, "Blazer 3D",
			NULL, NULL);
	}

	bWindow(int width, int height, const char* name) {
		window = glfwCreateWindow(width, height, name, NULL, NULL);
	}

	~bWindow() {
		glfwDestroyWindow(window);
	}

	GLFWwindow* getWindow() { return window; }
	void setWindowSize(int width, int height);
	void getWindowSize(int& width, int& height);
	void setCallback(const char* callback_name /*function pointer*/);
};