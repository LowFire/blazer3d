#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render.h"

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
	
	static Application* p_instance;
	std::unordered_map<std::string, std::unique_ptr<Window>> m_windows;
	Render* m_renderer;

	Application() {
		m_renderer = Render::getInstance();
	};

public:
	static Application* getInstance() { 
		if (p_instance == nullptr)
			p_instance = new Application;
		return p_instance;
	};

	void run();
	bool init();
	inline void close() { glfwTerminate(); }
};