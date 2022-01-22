#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glfw3.h>

class bApplication {
private:
	std::vector<GLFWwindow*> windows;

public:
	void run();
	int init();
};