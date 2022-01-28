#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "bApplication.h"

int main() {

	bApplication application;

	bool ok = application.init();
	if (ok)
		application.run();
	else return -1;
}