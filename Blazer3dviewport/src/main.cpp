#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

int main() {
	auto application = Application::getInstance();

	bool ok = application->init();
	if (ok)
		application->run();
	else {
		application->close();
		return -1;
	}

	application->close();
}