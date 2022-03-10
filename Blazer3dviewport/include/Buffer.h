#pragma once
#include <unordered_map>
#include <memory>
#include <vector>

#include "OpenglObject.h"

//namespace TestOpenglWrapperAPI
//{
//	class TestBuffer;
//}

class Buffer abstract : public OpenglObject
{
	//friend TestOpenglWrapperAPI::TestBuffer;
public:
	struct DataBlockAttribute
	{
		int index;
		GLsizeiptr size;
		GLintptr offset;
		GLenum type;
	};

private:
	GLint m_total_size;
	GLenum m_target;
	GLenum m_usage;
	bool m_is_initialized = false;
	std::unordered_map<int, DataBlockAttribute> m_data_attrib;
	/*static GLuint s_currently_bound_buf;*/

public:
	Buffer();
	Buffer(std::initializer_list<DataBlockAttribute> l);
	/*Buffer(Buffer& rhs);*/
	~Buffer();

	virtual void bind() abstract;
	virtual void unbind() abstract;
	virtual bool isBound() abstract;
	/*static void reset();*/

	void initData(std::vector<DataBlockAttribute> data_blocks);
	int getDataBlockCount(int index);
	GLsizeiptr getDataBlockSize(int index);
	GLenum getDataBlockType(int index);
	GLintptr getDataBlockOffset(int index);

	template <typename T>
	void writeData(int data_index, std::shared_ptr<T> data)
	{
		const auto& block = m_data_attrib.at(data_index);
		T* write_ptr = (T*)glMapNamedBufferRange(m_opengl_name,
			block.offset,
			block.size,
			GL_MAP_WRITE_BIT|GL_MAP_FLUSH_EXPLICIT_BIT);

		//Write data into the buffer
		int count = block.size / sizeof(T);
		for (int i = 0; i < count; i++)
		{
			write_ptr[i] = data.get()[i];
		}

		glFlushMappedNamedBufferRange(m_opengl_name, block.offset, block.size);
		glUnmapNamedBuffer(m_opengl_name);
		write_ptr = nullptr;
	}

	template <typename T>
	std::shared_ptr<T> readData(int data_index) //TODO: Have the function defer the type of data stored in the buffer based on block.type
	{
		const auto& block = m_data_attrib.at(data_index);
		T* read_ptr = (T*)glMapNamedBufferRange(m_opengl_name,
			block.offset,
			block.size,
			GL_MAP_READ_BIT);

		//Allocate memory to store data.
		auto data = std::shared_ptr<T>(new T[block.size]);

		for (int i = 0; i < block.size; i++)
		{
			data.get()[i] = read_ptr[i];
		}
		glUnmapNamedBuffer(m_opengl_name);
		return data;
	}

	/*Buffer& operator = (Buffer& rhs);*/
};