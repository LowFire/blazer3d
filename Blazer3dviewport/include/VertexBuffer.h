#pragma once

#include <memory>

#include "Buffer.h"
#include "VertexArray.h"

namespace TestOpenglWrapperAPI
{
	class TestVertexBuffer;
}

class VertexBuffer : public Buffer
{
	friend TestOpenglWrapperAPI::TestVertexBuffer;
private:
	std::shared_ptr<VertexArray> m_arrays;
	static GLuint s_currently_bound_vbo;

public:
	VertexBuffer();
	VertexBuffer(std::initializer_list<DataBlockAttribute>,
		std::shared_ptr<VertexArray> arrays);

	static void reset();

	void bind() override;
	void unbind() override;
	bool isBound() override;

	std::shared_ptr<VertexArray> getVertexArray();
	void setVertexArray(std::shared_ptr<VertexArray>);
};