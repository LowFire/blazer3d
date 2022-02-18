#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TestOpenglWrapperAPI {
	class TestApplication;
}

class Application {
	friend class TestOpenglWrapperAPI::TestApplication;
private:

	class Window {
	private:
		GLFWwindow* window;
		const char* name;
		int width;
		int height;

	public:
		
		Window() : width(800), height(640), name("Blazer 3D"){
			window = glfwCreateWindow(width, height, name, NULL, NULL);
		}

		Window(const Window& copy) {
			this->window = copy.window;
			this->name = copy.name;
			this->width = copy.width;
			this->height = copy.height;
		}

		~Window() {
			glfwDestroyWindow(window);
		}

		GLFWwindow* getWindow() { return window; }
		void setWindowSize(int width, int height);
		int getWindowWidth() { return width; }
		int getWindowHeight() { return height; }

		template <typename T>
		void setCallback(const char* callback_name, T function);
	}; 

	std::map<std::string, std::unique_ptr<Window>> windows;

public:
	void run();
	bool init();
	void close() { glfwTerminate(); }
};