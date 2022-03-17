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
			VertexBuffer buf;

			//Should create a VertexBuffer object with a bunch of default values.
			Assert::IsTrue(buf.m_opengl_name != 0);
			Assert::AreEqual((GLenum)GL_BUFFER, buf.m_object_type);
			Assert::AreEqual(std::to_string(buf.m_opengl_name), buf.m_label);
			Assert::AreEqual(0, buf.m_total_size);
			Assert::AreEqual((GLenum)GL_ARRAY_BUFFER, buf.m_target); //The target is the array VertexBuffer by default
			Assert::AreEqual((GLenum)GL_MAP_READ_BIT|GL_MAP_WRITE_BIT, buf.m_usage);
			Assert::AreEqual((size_t)0, buf.m_data_attrib.size());
			Assert::IsFalse(buf.m_is_initialized);

			//Test against the objects properties in the context.
			GLint64 size;
			GLint64 usage;
			GLchar* label = new GLchar[buf.m_label.size() + 1];

			glBindBuffer(GL_ARRAY_BUFFER, buf.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_STORAGE_FLAGS, &usage);
			glGetObjectLabel(GL_BUFFER,
				buf.m_opengl_name,
				buf.m_label.size() + 1,
				nullptr,
				label);

			Assert::AreEqual((GLint64)buf.m_total_size, size);
			Assert::AreEqual((GLint64)0, usage); //No storage was allocated yet.
			Assert::AreEqual(buf.m_label.c_str(), label);
			delete[] label;
		}

		TEST_METHOD(testDataBlockConstructor)
		{
			VertexBuffer buf1 = {
				{ 0, sizeof(float)* 6, 0,  GL_FLOAT },
				{ 1, sizeof(float) * 9, sizeof(float) * 6, GL_FLOAT }
			};

			Buffer::DataBlockAttribute pos = { 0, sizeof(float) * 9, 0, GL_FLOAT };
			Buffer::DataBlockAttribute color = { 1, sizeof(int) * 9, sizeof(float) * 9, GL_INT };

			VertexBuffer buf2 = { pos, color };

			//Create a VertexBuffer object and init memory for the data blocks.
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

			Assert::AreEqual((size_t)2, buf1.m_data_attrib.size());
			Assert::AreEqual((size_t)2, buf2.m_data_attrib.size());

			Assert::IsTrue(buf1.m_is_initialized);
			Assert::IsTrue(buf2.m_is_initialized);

			//Test against the objects properties in the context.
			GLint64 size;
			GLint64 usage;
			GLchar* label1 = new GLchar[buf1.m_label.size() + 1];

			glBindBuffer(GL_ARRAY_BUFFER, buf1.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_STORAGE_FLAGS, &usage);
			glGetObjectLabel(GL_BUFFER,
				buf1.m_opengl_name,
				buf1.m_label.size() + 1,
				nullptr,
				label1);

			Assert::AreEqual((GLint64)buf1.m_total_size, size);
			Assert::AreEqual((GLint64)buf1.m_usage, usage);
			Assert::AreEqual(buf1.m_label.c_str(), label1);
			delete[] label1;

			GLchar* label2 = new GLchar[buf2.m_label.size() + 1];

			glBindBuffer(GL_ARRAY_BUFFER, buf2.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_STORAGE_FLAGS, &usage);
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

		TEST_METHOD(testCopyConstructor)
		{
			VertexBuffer buf1({
				{ 0, sizeof(GLfloat) * 9, 0, GL_FLOAT }
			});
			auto data = std::shared_ptr<GLfloat>(new GLfloat[]{
				4.0f, 2.0f, 1.0f,
				4.0f, 5.0f, 4.0f,
				6.0f, 2.0f, 9.0f
			});
			buf1.writeData(0, data);

			VertexBuffer buf2(buf1);

			//Test if data has been copied over.
			auto buf1_data = buf1.readData<GLfloat>(0);
			auto buf2_data = buf2.readData<GLfloat>(0);
			for (int i = 0; i < 9; i++)
			{
				Assert::AreEqual(buf1_data.get()[i], buf2_data.get()[i]);
			}
		}

		TEST_METHOD(testDestructor)
		{
			GLuint name;
			{
				VertexBuffer buf;
				name = buf.m_opengl_name;
				glBindBuffer(GL_ARRAY_BUFFER, name);
				Assert::IsTrue(glIsBuffer(name));
			}
			Assert::IsFalse(glIsBuffer(name));
		}

		TEST_METHOD(testWriteData)
		{
			VertexBuffer buf = {
				{ 0, sizeof(float) * 6, 0, GL_FLOAT }
			};
			float* data = new float[]{
				0.0f, 0.5f,
				0.5f, -0.5f,
				-0.5f, -0.5f
			};
			auto ptr = std::shared_ptr<float>(data);
			buf.writeData(0, ptr);

			//Make sure the VertexBuffer is not mapped after operation is done
			GLint mapped;
			glBindBuffer(GL_ARRAY_BUFFER, buf.m_opengl_name);
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_MAPPED, &mapped);
			Assert::IsFalse(mapped);

			//Test to see if the data was written
			GLfloat* readBack = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER,
				0,
				buf.m_total_size,
				GL_MAP_READ_BIT);

			for (int i = 0; i < 6; i++)
			{
				Assert::AreEqual(data[i], readBack[i]);
			}
			glUnmapBuffer(GL_ARRAY_BUFFER);
			readBack = nullptr;
		}

		TEST_METHOD(testReadData)
		{
			VertexBuffer buf = {
				{ 0, sizeof(float) * 6, 0, GL_FLOAT }
			};
			float* data = new float[] {
				0.0f, 0.5f,
				0.5f, -0.5f,
				-0.5f, -0.5f
			};
			auto ptr = std::shared_ptr<float>(data);

			buf.writeData(0, ptr);
			auto readBack = buf.readData<float>(0);
			//Make sure the VertexBuffer is not mapped after operation is done
			GLint mapped;
			glBindBuffer(GL_ARRAY_BUFFER, buf.m_opengl_name);
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_MAPPED, &mapped);
			Assert::IsFalse(mapped);

			//Test to see if data was successfully read from the VertexBuffer.
			for (int i = 0; i < 6; i++)
			{
				Assert::AreEqual(data[i], (GLfloat)readBack.get()[i]);
			}
		}

		//TEST_METHOD(testBindAndUnbind)
		//{
		//	VertexBuffer buf1;
		//	VertexBuffer buf2;

		//	buf1.bind();
		//	Assert::IsTrue(buf1.isBound());
		//	Assert::IsFalse(buf2.isBound());
		//	Assert::AreEqual(VertexBuffer::s_currently_bound_vbo, buf1.m_opengl_name);
		//	Assert::AreNotEqual(VertexBuffer::s_currently_bound_vbo, buf2.m_opengl_name);

		//	buf1.unbind();
		//	Assert::IsFalse(buf1.isBound());
		//	Assert::AreNotEqual(VertexBuffer::s_currently_bound_vbo, buf1.m_opengl_name);
		//	Assert::AreEqual((GLuint)0, VertexBuffer::s_currently_bound_buf);

		//	buf2.bind();
		//	Assert::IsTrue(buf2.isBound());
		//	Assert::AreEqual(VertexBuffer::s_currently_bound_buf, buf2.m_opengl_name);
		//	buf1.unbind(); //This shouldn't unbind anything
		//	Assert::IsFalse(buf1.isBound());
		//	Assert::AreNotEqual(VertexBuffer::s_currently_bound_buf, buf1.m_opengl_name);

		//	buf2.unbind();
		//	Assert::IsFalse(buf2.isBound());
		//	Assert::AreNotEqual(VertexBuffer::s_currently_bound_buf, buf2.m_opengl_name);

		//	buf1.bind();
		//	VertexBuffer::reset();
		//	Assert::IsFalse(buf1.isBound());
		//	Assert::AreNotEqual(VertexBuffer::s_currently_bound_buf, buf1.m_opengl_name);

		//}

		/*TEST_METHOD(testGetAndSetLabel)
		{

		}*/

		/*TEST_METHOD(testGetOpenglName)
		{
			VertexBuffer buf;
			Assert::AreEqual(buf.m_opengl_name, buf.getOpenglName());
		}*/

		TEST_METHOD(testClearData)
		{

		}

		TEST_METHOD(testClearAll)
		{

		}

		TEST_METHOD(testInitData)
		{
			VertexBuffer buf;

			VertexBuffer::DataBlockAttribute pos{ 0, sizeof(float) * 6, 0, GL_FLOAT };
			VertexBuffer::DataBlockAttribute color{ 1, sizeof(float) * 9, sizeof(float) * 6, GL_FLOAT};

			Assert::IsFalse(buf.m_is_initialized);

			buf.initData(std::vector<VertexBuffer::DataBlockAttribute>{pos, color});

			//Test if VertexBuffer was initialized properly
			Assert::AreEqual((size_t)2, buf.m_data_attrib.size());

			GLint64 size;
			glBindBuffer(GL_ARRAY_BUFFER, buf.m_opengl_name);
			glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

			Assert::AreEqual((GLint64)buf.m_total_size, size);

			//Make sure you can't init data more than once.
			Buffer::DataBlockAttribute new_pos{ 3, sizeof(float) * 9, sizeof(float) * 15, GL_FLOAT };
			buf.initData(std::vector<Buffer::DataBlockAttribute>{new_pos});

			Assert::IsTrue(buf.m_is_initialized);
			Assert::AreNotEqual((size_t)3, buf.m_data_attrib.size());
		}

		TEST_METHOD(testDataBlockGettersAndSetters)
		{
			VertexBuffer buf;
			std::vector<Buffer::DataBlockAttribute> attrib {
				{ 0, sizeof(GLfloat) * 9, sizeof(GLfloat) * 6, GL_FLOAT },
			};

			buf.initData(attrib);
			//Test getters and setters
			Assert::AreEqual(9, buf.getDataBlockCount(0));
			Assert::AreEqual((GLsizeiptr)sizeof(GLfloat) * 9, buf.getDataBlockSize(0));
			Assert::AreEqual((GLintptr)sizeof(GLfloat) * 6, buf.getDataBlockOffset(0));
			Assert::AreEqual((GLenum)GL_FLOAT, buf.getDataBlockType(0));

			//Should return -1 if block cannot be found
			Assert::AreEqual(-1, buf.getDataBlockCount(1));
			Assert::AreEqual((GLsizeiptr)-1, buf.getDataBlockSize(1));
			Assert::AreEqual((GLintptr)-1, buf.getDataBlockOffset(1));
			Assert::AreEqual((GLenum)-1, buf.getDataBlockType(1));
		}

		//TEST_METHOD(testAssignemntOverload)
		//{
		//	VertexBuffer buf1({
		//		{ 0, sizeof(GLfloat) * 9, 0, GL_FLOAT }
		//		});
		//	auto buf1_pos = std::shared_ptr<GLfloat>(new GLfloat[]{
		//		4.0f, 2.0f, 1.0f,
		//		4.0f, 5.0f, 4.0f,
		//		6.0f, 2.0f, 9.0f
		//		});
		//	buf1.writeData(0, buf1_pos);

		//	VertexBuffer buf2({
		//		{ 0, sizeof(GLfloat) * 9, 0, GL_FLOAT },
		//		{ 1, sizeof(GLuint) * 9, sizeof(GLfloat) * 9, GL_UNSIGNED_INT }
		//	});
		//	auto buf2_pos = std::shared_ptr<GLfloat>(new GLfloat[]{
		//		5.5f, 2.4f, 9.0f,
		//		6.5f, 1.4f, 6.6f,
		//		7.4f, 23.1f, 8.2f
		//	});
		//	auto buf2_color = std::shared_ptr<GLuint>(new GLuint[]{
		//		234, 123, 45,
		//		223, 145, 210,
		//		45, 22, 122
		//	});
		//	buf2.writeData(0, buf2_pos);
		//	buf2.writeData(1, buf2_color);

		//	buf1 = buf2;

		//	//Test if data has been copied and replaced.
		//	auto buf1_posdata = buf1.readData<GLfloat>(0);
		//	auto buf1_colordata = buf1.readData<GLuint>(1);
		//	auto buf2_posdata = buf2.readData<GLfloat>(0);
		//	auto buf2_colordata = buf2.readData<GLuint>(1);

		//	//Compare position data
		//	for (int i = 0; i < 9; i++)
		//	{
		//		Assert::AreEqual(buf1_posdata.get()[i], buf2_posdata.get()[i]);
		//	}

		//	//Compare color data
		//	for (int i = 0; i < 9; i++)
		//	{
		//		Assert::AreEqual(buf1_colordata.get()[i], buf2_colordata.get()[i]);
		//	}
		//}
	};
}