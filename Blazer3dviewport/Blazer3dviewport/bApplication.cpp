
#include "bApplication.h"

void bApplication::run() {
	while (!glfwWindowShouldClose(getWindow("main").window)) {
		glfwPollEvents();
		glfwSwapBuffers(getWindow("main").window);
	}
	glfwTerminate();
}

bool bApplication::init() {

	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Create windows
	bWindow new_window;
	if (new_window.window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(new_window.window);
	windows.insert(std::pair<std::string, bWindow>("main", new_window));

	//Get opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	int window_width;
	int window_height;
	new_window.getWindowSize(window_width, window_height);
	glViewport(0, 0, window_width, window_height);

	return true;
}

bApplication::bWindow bApplication::getWindow(const char* window_name) {
	return windows.at(window_name);
}

void bApplication::destroyWindow(const char* window_name) {
	GLFWwindow* removing_window = windows.at(window_name).window;
	glfwDestroyWindow(removing_window);
	windows.erase(window_name);
}


//bWindow function implementations
void bApplication::bWindow::setWindowSize(int width, int height) {
	glfwSetWindowSize(window, width, height);
}

void bApplication::bWindow::getWindowSize(int& width, int& height) {
	glfwGetWindowSize(window, &width, &height);
}

template <typename T>
void bApplication::bWindow::setCallback(const char* callback_name, T callback_function) {

}