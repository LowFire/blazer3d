#pragma once

#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <glfw3.h>

class bApplication {
private:

	class bWindow {
	public:
		GLFWwindow* window;

		bWindow(int width = 800, int height = 640, const char* name = "Blazer 3D") {
			window = glfwCreateWindow(width, height, name, NULL, NULL);
		}

		bWindow(const bWindow& copy) {
			this->window = copy.window;
		}

		void setWindowSize(int width, int height);
		void getWindowSize(int& width, int& height);

		template <typename T>
		void setCallback(const char* callback_name, T function);
	}; 

	std::map<std::string, bWindow> windows;

public:
	void run();
	bool init();
	void destroyWindow(const char* window_name);
	bWindow getWindow(const char* window_name);
};