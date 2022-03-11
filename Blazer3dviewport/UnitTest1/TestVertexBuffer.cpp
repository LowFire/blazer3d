#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "VertexBuffer.h"

#include <GLFW/glfw3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestVertexBuffer)
	{
		TEST_CLASS_INITIALIZE(InitApplication)
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
		}

		TEST_CLASS_CLEANUP(DestroyApplication)
		{
			glfwTerminate();
		}

		TEST_METHOD(testDefaultConstruction)
		{
			/*In default construction, a buffer object is created with no initialized storage
			and the reference to the vertex array is nullptr. The buffer needs to be initialized
			to be used.*/

			VertexBuffer buf;

			auto array_ptr = 
		}

		TEST_METHOD(testDataBlockConstruction)
		{

		}

		TEST_METHOD(TestBindAndUnbind)
		{

		}

		TEST_METHOD(testGetAndSetVertexArray)
		{

		}
	};
}