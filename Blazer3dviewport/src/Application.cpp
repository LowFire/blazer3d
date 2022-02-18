
#include "Application.h"

void Application::run() {
	while (!glfwWindowShouldClose(windows.at("main")->getWindow())) {
		glfwPollEvents();
		glfwSwapBuffers(windows.at("main")->getWindow());
	}
}

bool Application::init() {

	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	//Create windows
	windows.insert(std::pair<std::string, std::unique_ptr<Window>>(
		"main",
		new Window()
		));

	if (windows.at("main")->getWindow() == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		return false;
	}
	
	glfwMakeContextCurrent(windows.at("main")->getWindow());


	//Get opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	int window_width = windows.at("main")->getWindowWidth();
	int window_height = windows.at("main")->getWindowHeight();
	glViewport(0, 0, window_width, window_height);

	return true;
}

//bWindow function implementations
void Application::Window::setWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
	glfwSetWindowSize(window, width, height);
}

template <typename T>
void Application::Window::setCallback(const char* callback_name, T callback_function) {

}