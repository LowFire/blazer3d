#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TestOpenglWrapperAPI {
	class TestbApplication;
}

class bApplication {
	friend class TestOpenglWrapperAPI::TestbApplication;
private:

	class bWindow {
	private:
		GLFWwindow* window;
		const char* name;
		int width;
		int height;

	public:
		
		bWindow() : width(800), height(640), name("Blazer 3D"){
			window = glfwCreateWindow(width, height, name, NULL, NULL);
		}

		bWindow(const bWindow& copy) {
			this->window = copy.window;
			this->name = copy.name;
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
	void close() { glfwTerminate(); }
};