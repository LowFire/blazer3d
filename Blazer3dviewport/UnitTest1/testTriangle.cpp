//#include "pch.h"
//#include "CppUnitTest.h"
//
//#include <iostream>
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include "Triangle.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace TestOpenglWrapperAPI
//{
//	TEST_CLASS(testTriangle)
//	{
//		TEST_CLASS_INITIALIZE(CreateApplication)
//		{
//			glfwInit();
//
//			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
//
//			//Create windows
//			GLFWwindow* window = glfwCreateWindow(800, 640, "Test", NULL, NULL);
//
//			if (window == nullptr) {
//				std::cout << "Failed to create window" << std::endl;
//			}
//
//			glfwMakeContextCurrent(window);
//
//			//Get opengl functions
//			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//			{
//				std::cout << "Failed to initialize GLAD" << std::endl;
//			}
//
//			glViewport(0, 0, 800, 640);
//		}
//
//		TEST_CLASS_CLEANUP(DestroyApplication)
//		{
//			glfwTerminate();
//		}
//
//		TEST_METHOD(testDefaultConstructor)
//		{
//			Triangle t;
//
//			Assert::AreEqual(3, t.getVertCount());
//			
//			auto buffer = t.getBuffer();
//			auto pos = buffer->readData<GLfloat>(0);
//			auto expected = std::make_unique<GLfloat>(0.1f, 0.1f, 0.1f);
//
//			for (int i = 0; i < 3; i++)
//			{
//				Assert::AreEqual(expected.get()[i], pos.get()[i]);
//			}
//		}
//
//		TEST_METHOD(testNonDefaultConstructor)
//		{
//
//		}
//
//		TEST_METHOD(testDraw)
//		{
//
//		}
//	};
//}