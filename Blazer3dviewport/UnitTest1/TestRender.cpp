#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <vector>

#include "Render.h"

#include <GLFW/glfw3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestRender)
	{

		TEST_CLASS_CLEANUP(DestroyApplication)
		{
			glfwTerminate();
		}

		TEST_METHOD(TestUpdate)
		{
			glfwInit();

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

			//Create windows
			GLFWwindow* window = glfwCreateWindow(800, 640, "Test", NULL, NULL);

			if (window == nullptr) {
				std::cout << "Failed to create window" << std::endl;
			}

			glfwMakeContextCurrent(window);

			//Get opengl functions
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
			}

			glViewport(0, 0, 800, 640);

			Render* renderer = Render::getInstance();
			Draw a_triangle;
			std::vector<Draw> draw_objects{ a_triangle };
			renderer->setDrawObjects(draw_objects);
			renderer->update(window);
		}
	};
}