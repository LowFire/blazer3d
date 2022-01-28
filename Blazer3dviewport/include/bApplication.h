#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <glfw3.h>

class bApplication {
private:

	class bWindow {
	private:
		GLFWwindow* window;
		int width;
		int height;

	public:
		
		bWindow(int width = 800, int height = 640, const char* name = "Blazer 3D") {
			window = glfwCreateWindow(width, height, name, NULL, NULL);
			this->width = width;
			this->height = height;
		}

		bWindow(const bWindow& copy) {
			this->window = copy.window;
			this->width = copy.width;
			this->height = copy.height;
		}

		~bWindow() {
			glfwDestroyWindow(window);
		}

		GLFWwindow* getWindow() { return window; }
		void setWindowSize(int width, int height);
		int getWindowWidth() { return width; }
		int getWindowHeight() { return height; }

		template <typename T>
		void setCallback(const char* callback_name, T function);
	}; 

	std::map<std::string, std::unique_ptr<bWindow>> windows;

public:
	void run();
	bool init();
};