#pragma once
#include <unordered_map>
#include <memory>
#include <vector>

#include <glad/glad.h>

#include "OpenglObject.h"

namespace TestOpenglWrapperAPI
{
	class TestBuffer;
}

class Buffer : public OpenglObject
{
	friend TestOpenglWrapperAPI::TestBuffer;
public:
	struct DataBlockAttribute
	{
		int index;
		GLsizeiptr size;
		GLintptr offset;
		GLenum type;
	};

private:
	GLbyte* p_data;
	GLint m_total_size;
	GLenum m_target;
	GLenum m_usage;
	std::unordered_map<int, DataBlockAttribute> m_data_attrib;
	static GLuint s_currently_bound_buf;

public:
	Buffer();
	Buffer(std::initializer_list<DataBlockAttribute> l);
	~Buffer();

	virtual void bind() override;
	virtual void unbind() override;
	bool isBound();
	static void reset();

	//template <typename T>
	void writeData(int data_index, std::shared_ptr<GLbyte> data);
	template <typename T>
	std::shared_ptr<T> readData(int data_index);

};