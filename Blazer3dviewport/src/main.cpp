#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bApplication.h"

int main() {

	bApplication application;

	bool ok = application.init();
	if (ok)
		application.run();
	else {
		application.close();
		return -1;
	}

	application.close();
}