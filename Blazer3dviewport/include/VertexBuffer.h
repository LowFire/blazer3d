#pragma once

#include <memory>

#include "Buffer.h"
#include "VertexArray.h"

namespace TestOpenglWrapperAPI
{
	class TestVertexBuffer;
	class TestBuffer;
}

class VertexBuffer : public Buffer
{
	friend TestOpenglWrapperAPI::TestVertexBuffer;
	friend TestOpenglWrapperAPI::TestBuffer;
private:
	std::shared_ptr<VertexArray> m_arrays;
	static GLuint s_currently_bound_vbo;

public:
	VertexBuffer();
	VertexBuffer(std::initializer_list<DataBlockAttribute> l);
	VertexBuffer(std::initializer_list<DataBlockAttribute>,
		std::initializer_list<VertexArray::VertexAttribute> arrays);

	static void reset();

	void bind() override;
	void unbind() override;
	bool isBound() override;

	std::shared_ptr<VertexArray> getVertexArray();
	void setVertexArray(std::shared_ptr<VertexArray>);
	void makeVertexArray(std::initializer_list<VertexArray::VertexAttribute> a);
};