#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Draw.h"

#include <GLFW/glfw3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestDraw)
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
			Draw triangle;

			//We want all the data to be set to draw a basic triangle (for now)
			Assert::AreEqual(3, triangle.getVertCount());
			Assert::AreEqual(glm::vec3(0), triangle.m_origin);
			Assert::AreEqual(glm::vec3(0), triangle.position);
			Assert::AreEqual(glm::vec3(0), triangle.rotation);
			Assert::AreEqual(glm::vec3(1), triangle.scale);

			//Test if data has been set in the buffer object.
			Assert::AreEqual(1, triangle.m_buffer.getDataBlockCount());
			Assert::AreEqual(sizeof(float) * 9, triangle.m_buffer.getDataBlockSize(0));

			std::vector<GLfloat> expected_data{
				0.0f, 0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f
			};

			std::shared_ptr<GLfloat> actual_data = triangle.m_buffer.readData<GLfloat>(0);

			for (int i = 0; i < expected_data.size(); i++)
			{
				Assert::AreEqual(expected_data.at(i), actual_data.get()[i]);
				i++;
			}

			//Test if vertex attributes have been set.
			std::vector<VertexArray::VertexAttribute> attribs = triangle.m_arrays.getAllAttributes();
			Assert::AreEqual((size_t)1, attribs.size());
			Assert::AreEqual((GLuint)0, attribs.at(0).index);
			Assert::AreEqual((GLenum)GL_FLOAT, attribs.at(0).type);
			Assert::AreEqual(3, attribs.at(0).size);
			Assert::AreEqual((GLboolean)GL_FALSE, attribs.at(0).normalized);
			Assert::AreEqual(0, attribs.at(0).stride);
			Assert::AreEqual((void*)0, attribs.at(0).offset);
			Assert::IsTrue(attribs.at(0).enabled);
		}

		TEST_METHOD(testDraw)
		{

		}

		TEST_METHOD(testSetAndGetOrigin)
		{

		}

		TEST_METHOD(testGetAndSetVertexArray)
		{

		}

		TEST_METHOD(testGetAndSetBuffer)
		{

		}

		TEST_METHOD(testGetVertCount)
		{

		}
	};
};