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
			to be used. The base class default constructor is called.*/

			VertexBuffer buf;

			auto array_ptr = buf.getVertexArray();
			Assert::IsNull(array_ptr.get());
		}

		TEST_METHOD(testDataBlockConstruction)
		{
			/*Buffer storage is allocated using the passed in data block attributes
			A refernce to a VertexArray is set to describe the layout of the vertex
			buffer data.*/

			Buffer::DataBlockAttribute pos{ 0, sizeof(GLfloat) * 9, 0, GL_FLOAT };
			Buffer::DataBlockAttribute color{ 0, sizeof(GLfloat) * 9, sizeof(GLfloat) * 9, GL_FLOAT };
			Buffer::DataBlockAttribute uv{ 0, sizeof(GLfloat) * 6, sizeof(GLfloat) * 18, GL_FLOAT };

			/*NOTE: There's a problem here. Vertex array attributes cannot be created until there is a buffer
			with allocated storage bound to the GL_ARRAY_BUFFER target, otherwise opengl will throw an
			error. It might make sense to have this constructor implcitly generate vertex arrays based
			on the data block attributes passed in. This might require some refactoring of the VertexArray
			class.*/
			VertexArray::VertexAttribute pos_attrib { 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 };
			VertexArray::VertexAttribute color_attrib { 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 9) };
			VertexArray::VertexAttribute uv_attrib{ 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 18) };

			auto arrays = std::make_shared<VertexArray>(pos_attrib, color_attrib, uv_attrib);

			VertexBuffer buf({ pos, color, uv }, arrays);

			Assert::AreSame(buf.getVertexArray().get(), arrays.get());
		}

		TEST_METHOD(TestBindAndUnbind)
		{
			/*Test to make sure that vertex buffers are bound and unbound to the GL_ARRAY_BUFFER target*/
			VertexBuffer buf1;
			VertexBuffer buf2;

			Assert::AreEqual(buf1.m_target, (GLenum)GL_ARRAY_BUFFER);
			Assert::AreEqual(buf2.m_target, (GLenum)GL_ARRAY_BUFFER);

			Assert::IsFalse(buf1.isBound());
			Assert::IsFalse(buf2.isBound());
			Assert::AreEqual((GLuint)0, VertexBuffer::s_currently_bound_vbo);

			buf1.bind();
			Assert::IsTrue(buf1.isBound());
			Assert::AreEqual(buf1.getOpenglName(), VertexBuffer::s_currently_bound_vbo);

			buf2.bind();
			Assert::IsTrue(buf2.isBound());
			Assert::IsFalse(buf1.isBound());
			Assert::AreEqual(buf2.getOpenglName(), VertexBuffer::s_currently_bound_vbo);

			VertexBuffer::reset();
			Assert::IsFalse(buf1.isBound());
			Assert::IsFalse(buf2.isBound());
			Assert::AreEqual((GLuint)0, VertexBuffer::s_currently_bound_vbo);
		}

		TEST_METHOD(testGetAndSetVertexArray)
		{
			VertexArray::VertexAttribute pos_attrib{ 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 };
			VertexArray::VertexAttribute color_attrib{ 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 9) };
			VertexArray::VertexAttribute uv_attrib{ 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 18) };

			auto arrays = std::make_shared<VertexArray>(pos_attrib, color_attrib, uv_attrib);

			VertexBuffer buf;

		}
	};
}