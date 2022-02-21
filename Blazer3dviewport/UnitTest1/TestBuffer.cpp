#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Buffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestBuffer)
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

		TEST_METHOD(testDefaultConstructor)
		{
			Buffer buf;

			//Should create a buffer object but not init anything.
			Assert::IsTrue(buf.m_opengl_name != 0);
			Assert::AreEqual((GLenum)GL_BUFFER, buf.m_object_type);
			Assert::AreEqual(std::to_string(buf.m_opengl_name), buf.m_label);
			Assert::AreEqual(0, buf.m_total_size);
			Assert::AreEqual((GLenum)GL_ARRAY_BUFFER, buf.m_target); //The target is the array buffer by default
			Assert::AreEqual((GLbyte*)nullptr, buf.p_data);
			Assert::AreEqual((size_t)0, buf.m_data_attrib.size());

		}

		TEST_METHOD(testDataBlockConstructor)
		{

		}

		TEST_METHOD(testDestructor)
		{

		}

		TEST_METHOD(testWriteData)
		{

		}

		TEST_METHOD(testReadData)
		{

		}

		TEST_METHOD(testBindAndUnbind)
		{

		}

		TEST_METHOD(testGetAndSetLabel)
		{

		}

		TEST_METHOD(testGetOpenglName)
		{

		}

		TEST_METHOD(testClearData)
		{

		}

		TEST_METHOD(testClearAll)
		{

		}

		TEST_METHOD(testAddDataBlock)
		{

		}
	};
}