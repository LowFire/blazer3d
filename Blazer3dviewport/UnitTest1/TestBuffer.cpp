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

			//Should create a buffer object with a bunch of default values.
			Assert::IsTrue(buf.m_opengl_name != 0);
			Assert::AreEqual((GLenum)GL_BUFFER, buf.m_object_type);
			Assert::AreEqual(std::to_string(buf.m_opengl_name), buf.m_label);
			Assert::AreEqual(0, buf.m_total_size);
			Assert::AreEqual((GLenum)GL_ARRAY_BUFFER, buf.m_target); //The target is the array buffer by default
			Assert::AreEqual((GLenum)GL_DYNAMIC_STORAGE_BIT, buf.m_usage);
			Assert::AreEqual((GLbyte*)nullptr, buf.p_data);
			Assert::AreEqual((size_t)0, buf.m_data_attrib.size());

			//Test against the objects properties in the context.
			GLint64 size;
			GLint64 usage;
			GLchar* label = new GLchar[buf.m_label.size() + 1];

			glBindBuffer(GL_ARRAY_BUFFER, buf.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);
			glGetObjectLabel(GL_BUFFER,
				buf.m_opengl_name,
				buf.m_label.size() + 1,
				nullptr,
				label);

			Assert::AreEqual((GLint64)buf.m_total_size, size);
			Assert::AreEqual((GLint64)buf.m_usage, usage);
			Assert::AreEqual(buf.m_label.c_str(), label);
			delete[] label;
		}

		TEST_METHOD(testDataBlockConstructor)
		{
			Buffer buf1 = {
				{ sizeof(float)* 6, 0,  GL_FLOAT },
				{ sizeof(float) * 9, sizeof(float) * 6, GL_FLOAT }
			};

			Buffer::DataBlockAttribute pos = { sizeof(float) * 9, 0, GL_FLOAT };
			Buffer::DataBlockAttribute color = { sizeof(int) * 9, sizeof(float) * 9, GL_INT };

			Buffer buf2 = { pos, color };

			//Create a buffer object and init memory for the data blocks.
			Assert::IsTrue(buf1.m_opengl_name != 0);
			Assert::IsTrue(buf2.m_opengl_name != 0);

			Assert::AreEqual((GLenum)GL_BUFFER, buf1.m_object_type);
			Assert::AreEqual((GLenum)GL_BUFFER, buf2.m_object_type);

			Assert::AreEqual(std::to_string(buf1.m_opengl_name), buf1.m_label);
			Assert::AreEqual(std::to_string(buf2.m_opengl_name), buf2.m_label);

			Assert::AreEqual((int)((sizeof(GLfloat) * 6) + (sizeof(GLfloat) * 9)), buf1.m_total_size);
			Assert::AreEqual((int)((sizeof(GLfloat) * 9) + (sizeof(GLint) * 9)), buf2.m_total_size);

			Assert::AreEqual((GLenum)GL_ARRAY_BUFFER, buf1.m_target);
			Assert::AreEqual((GLenum)GL_ARRAY_BUFFER, buf2.m_target);

			Assert::AreEqual((GLbyte*)nullptr, buf1.p_data);
			Assert::AreEqual((GLbyte*)nullptr, buf2.p_data);

			Assert::AreEqual((size_t)2, buf1.m_data_attrib.size());
			Assert::AreEqual((size_t)2, buf2.m_data_attrib.size());

			//Test against the objects properties in the context.
			GLint64 size;
			GLint64 usage;
			GLchar* label1 = new GLchar[buf1.m_label.size() + 1];

			glBindBuffer(GL_ARRAY_BUFFER, buf1.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);
			glGetObjectLabel(GL_BUFFER,
				buf1.m_opengl_name,
				buf1.m_label.size() + 1,
				nullptr,
				label1);

			Assert::AreEqual((GLint64)buf1.m_total_size, size);
			Assert::AreEqual((GLint64)buf1.m_usage, usage);
			Assert::AreEqual(buf2.m_label.c_str(), label1);
			delete[] label1;

			GLchar* label2 = new GLchar[buf2.m_label.size() + 1];

			glBindBuffer(GL_ARRAY_BUFFER, buf2.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);
			glGetObjectLabel(GL_BUFFER,
				buf2.m_opengl_name,
				buf2.m_label.size() + 1,
				nullptr,
				label2);

			Assert::AreEqual((GLint64)buf2.m_total_size, size);
			Assert::AreEqual((GLint64)buf2.m_usage, usage);
			Assert::AreEqual(buf2.m_label.c_str(), label2);

			//Test if memory has been allocated for data blocks
			GLint64 buf1_size;
			GLint64 buf2_size;
			glBindBuffer(GL_ARRAY_BUFFER, buf1.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buf1_size);
			glBindBuffer(GL_ARRAY_BUFFER, buf2.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buf2_size);
			Assert::AreEqual((GLint64)buf1.m_total_size, buf1_size);
			Assert::AreEqual((GLint64)buf2.m_total_size, buf2_size);
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