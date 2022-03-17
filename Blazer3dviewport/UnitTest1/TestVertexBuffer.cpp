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

			//Target should be the array buffer.
			Assert::AreEqual((GLenum)GL_ARRAY_BUFFER, buf.m_target);
		}

		TEST_METHOD(testDataBlockConstruction)
		{
			/*Buffer storage is allocated using the passed in data block attributes
			A VertexArray is created implicitly using the passed in VertexAttributes.
			VertexArrays must always be created implicitly.*/

			Buffer::DataBlockAttribute pos{ 0, sizeof(GLfloat) * 9, 0, GL_FLOAT };
			Buffer::DataBlockAttribute color{ 0, sizeof(GLfloat) * 9, sizeof(GLfloat) * 9, GL_FLOAT };
			Buffer::DataBlockAttribute uv{ 0, sizeof(GLfloat) * 6, sizeof(GLfloat) * 18, GL_FLOAT };

			VertexArray::VertexAttribute pos_attrib { 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 };
			VertexArray::VertexAttribute color_attrib { 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 9) };
			VertexArray::VertexAttribute uv_attrib{ 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 18) };

			VertexBuffer buf({ pos, color, uv }, {pos_attrib, color_attrib, uv_attrib});

			//Test if the vertex array was successfully created
			auto arr = buf.getVertexArray();

			GLint size;
			GLint type;
			GLint normalized;
			GLint stride;
			void* offset;

			arr->bind();
			//Attribute index 0
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)0, offset);

			//Attribute index 1
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(1, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)(sizeof(GLfloat) * 9), offset);

			//Attribute index 2
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(2, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(2, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)(sizeof(GLfloat) * 18), offset);
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

		/*TEST_METHOD(testGetAndSetVertexArray)
		{
			VertexArray::VertexAttribute pos_attrib{ 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 };
			VertexArray::VertexAttribute color_attrib{ 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 9) };
			VertexArray::VertexAttribute uv_attrib{ 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 18) };

			auto arrays = std::make_shared<VertexArray>();
			arrays->addAttributes({ pos_attrib, color_attrib, uv_attrib });

			VertexBuffer buf;
		}*/

		TEST_METHOD(testMakeVertexArray)
		{
			/*Creates a new vertex array and replaces the current one*/

			Buffer::DataBlockAttribute pos{ 0, sizeof(GLfloat) * 9, 0, GL_FLOAT };
			Buffer::DataBlockAttribute color{ 0, sizeof(GLfloat) * 9, sizeof(GLfloat) * 9, GL_FLOAT };
			Buffer::DataBlockAttribute uv{ 0, sizeof(GLfloat) * 6, sizeof(GLfloat) * 18, GL_FLOAT };

			VertexArray::VertexAttribute pos_attrib{ 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 };
			VertexArray::VertexAttribute color_attrib{ 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 9) };
			VertexArray::VertexAttribute uv_attrib{ 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 18) };

			VertexBuffer buf({ pos, color, uv });

			buf.makeVertexArray({ pos_attrib, color_attrib, uv_attrib });
			auto arr = buf.getVertexArray();

			GLint size;
			GLint type;
			GLint normalized;
			GLint stride;
			void* offset;

			arr->bind();
			//Attribute index 0
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)0, offset);

			//Attribute index 1
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(1, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)(sizeof(GLfloat) * 9), offset);

			//Attribute index 2
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(2, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(2, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)(sizeof(GLfloat) * 18), offset);

			VertexArray::VertexAttribute pos_attrib2{ 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 };
			VertexArray::VertexAttribute color_attrib2{ 1, 2, GL_UNSIGNED_INT, GL_TRUE, 0, (void*)(sizeof(GLfloat) * 6) };

			//Should replace the current vertex array
			buf.makeVertexArray({ pos_attrib2, color_attrib2 });
			arr.reset();
			arr = buf.getVertexArray();

			arr->bind();
			//Attribute index 0
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(3, size);
			Assert::AreEqual(GL_FLOAT, type);
			Assert::AreEqual(GL_FALSE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)0, offset);

			//Attribute index 1
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexAttribPointerv(1, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

			Assert::AreEqual(2, size);
			Assert::AreEqual(GL_UNSIGNED_INT, type);
			Assert::AreEqual(GL_TRUE, normalized);
			Assert::AreEqual(0, stride);
			Assert::AreEqual((void*)(sizeof(GLfloat) * 6), offset);
		}
	};
}