#pragma once

#include <vector>

#include "Buffer.h"

namespace TestOpenglWrapperAPI
{
	class TestIndexBuffer;
}

class IndexBuffer : public Buffer
{
	friend TestOpenglWrapperAPI::TestIndexBuffer;
private:
	static GLuint s_currently_bound_ebo;
	int m_indicies_count;

public:
	IndexBuffer();
	IndexBuffer(std::initializer_list<GLuint> l);
	
	static void reset();
	void bind() override;
	void unbind() override;
	bool isBound() override;

	void setIndicies(std::initializer_list<GLuint> l);
	std::vector<GLuint> getIndicies();
	int getIndiciesCount() { return m_indicies_count; }
};