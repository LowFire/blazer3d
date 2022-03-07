
#include "Application.h"

Application* Application::p_instance = nullptr;

//MAIN PROGRAM LOOP
void Application::run() {
	//create some triangles to draw.
	Draw triangle;
	std::vector<Draw> objects{ triangle };
	m_renderer->setDrawObjects(objects);
	while (!glfwWindowShouldClose(m_windows.at("main")->getWindow())) {
		glfwPollEvents();
		m_renderer->update(getCurrentWindow());
	}
}

bool Application::init() {

	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	//Create windows
	m_windows.insert(std::pair<std::string, std::unique_ptr<Window>>(
		"main",
		new Window()
		));

	if (m_windows.at("main")->getWindow() == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		return false;
	}
	
	glfwMakeContextCurrent(m_windows.at("main")->getWindow());
	m_current_window = "main";


	//Get opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	int window_width = m_windows.at("main")->getWindowWidth();
	int window_height = m_windows.at("main")->getWindowHeight();
	m_windows.at("main")->setClearColor({ 0.3f, 0.0f, 0.0f });
	glViewport(0, 0, window_width, window_height);

	return true;
}

//Window function implementations
void Application::Window::setWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
	glfwSetWindowSize(window, width, height);
}

template <typename T>
void Application::Window::setCallback(const char* callback_name, T callback_function) {

}

void Application::makeWindowCurrent(const std::string& name)
{
	auto it = m_windows.find(name);
	if (it != m_windows.end())
	{ 
		GLFWwindow* window = it->second->getWindow();
		glfwMakeContextCurrent(window);
		m_current_window = name;

	}
}

GLFWwindow* Application::getCurrentWindow()
{
	auto it = m_windows.find(m_current_window);
	if (it != m_windows.end())
		return it->second->getWindow();
	return nullptr; //Error. This function should never return null.
}