#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "IndexBuffer.h"

#include <GLFW/glfw3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestIndexBuffer)
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

		TEST_METHOD(TestDefaultConstructor)
		{
			/*The default constructor will call the parent class constructor, and then
			set the bind target to GL_ELEMENT_ARRAY_BUFFER. The buffer is left
			uninitialized.*/

			IndexBuffer buf;

			Assert::AreEqual((GLenum)GL_ELEMENT_ARRAY_BUFFER, buf.m_target);
			Assert::AreEqual(0, buf.m_indicies_count);
		}

		TEST_METHOD(TestIndiciesConstructor)
		{
			/*The indicies constructor will create and initialize the index buffer
			with the array of indicies passed into the constructor. The indicies
			must always be unsigned integers. Once the buffer has been initialized with
			indicies, the buffer will remember the number of indicies stored and will require
			that exact amount of indicies to be written to the buffer*/

			IndexBuffer buf{ 0, 1, 2, 3 };

			Assert::AreEqual(4, buf.getCount());

			auto indicies = buf.getIndicies();

			for (GLuint i = 0; i < buf.getCount(); i++)
			{
				Assert::AreEqual(i, indicies.at(i));
			}

			IndexBuffer buf2;
			indicies = { 3, 4, 5 };

			buf2.setIndicies(indicies);
			indicies = buf2.getIndicies();
			for (GLuint i = 0; i < buf2.getCount(); i++)
			{
				Assert::AreEqual(i + 3, indicies.at(i));
			}

			buf2.setIndicies({ 4, 5 }); //Shouldn't work
			indicies = buf2.getIndicies();
			for (GLuint i = 0; i < buf2.getCount(); i++)
			{
				Assert::AreEqual(i + 3, indicies.at(i));
			}

			buf2.setIndicies({ 4, 5, 6 });
			indicies = buf2.getIndicies();
			for (GLuint i = 0; i < buf2.getCount(); i++)
			{
				Assert::AreEqual(i + 4, indicies.at(i));
			}
		}

		TEST_METHOD(TestSetAndGetIndicies)
		{
			/*getIndicies and setIndicies will read and write to and from the index buffer
			getIndicies will return a vector of the indicies stored in the index buffer.
			setIndicies expects the same number of indicies as indicated by getCount() otherwise
			an exception will be thrown. If getCount returns zero, setIndicies will initialize the buffer
			with the passed in indicies and set the count of the indicies to the number passed in.*/

			IndexBuffer buf{ 1, 2, 3, 4 };

			auto indicies = buf.getIndicies();

			for (GLuint i = 0; i < buf.getCount(); i++)
			{
				Assert::AreEqual(i + 1, indicies.at(i));
			}

			buf.setIndicies({ 2, 3, 4 }); //Shouldn't work. 4 indicies are expected.
			indicies = buf.getIndicies();

			for (GLuint i = 0; i < buf.getCount(); i++)
			{
				Assert::AreEqual(i + 1, indicies.at(i));
			}

			buf.setIndicies({ 3, 4, 5, 6 });
			indicies = buf.getIndicies();

			for (GLuint i = 0; i < buf.getCount(); i++)
			{
				Assert::AreEqual(i + 3, indicies.at(i));
			}
		}

		TEST_METHOD(TestBindAndUnbind)
		{
			/*Test binding and unbinding. s_currently_bound_ebo should
			always keep track of the index buffer currently bound to
			GL_ELEMENT_ARRAY_BUFFER*/

			IndexBuffer buf1;
			IndexBuffer buf2;

			Assert::AreEqual((GLuint)0, IndexBuffer::s_currently_bound_ebo);
			Assert::IsFalse(buf1.isBound());
			Assert::IsFalse(buf2.isBound());

			buf1.bind();
			Assert::IsTrue(buf1.isBound());
			Assert::AreEqual(buf1.m_opengl_name, IndexBuffer::s_currently_bound_ebo);

			buf2.bind();
			Assert::IsTrue(buf2.isBound());
			Assert::IsFalse(buf1.isBound());
			Assert::AreEqual(buf2.m_opengl_name, IndexBuffer::s_currently_bound_ebo);

			IndexBuffer::reset();
			Assert::IsFalse(buf1.isBound());
			Assert::IsFalse(buf2.isBound());
			Assert::AreEqual((GLuint)0, IndexBuffer::s_currently_bound_ebo);
		}

		TEST_METHOD(TestGetIndiciesCount)
		{
			/*Test the getter function that returns the number of indicies
			stored in the index buffer*/

			IndexBuffer buf{ 1, 2, 3, 4 };

			int count = buf.getCount();
			Assert::AreEqual(4, count);
		}
	};
}