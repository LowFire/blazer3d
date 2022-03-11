#include "VertexBuffer.h"

int VertexBuffer::s_currently_bound_vbo = 0;

VertexBuffer::VertexBuffer()
{

}
VertexBuffer::VertexBuffer(std::initializer_list<DataBlockAttribute>,
	std::shared_ptr<VertexArray> arrays)
{

}

void VertexBuffer::reset()
{

}

std::shared_ptr<VertexArray> VertexBuffer::getVertexArray()
{
	return nullptr;
}

void VertexBuffer::setVertexArray(std::shared_ptr<VertexArray>)
{

}

void VertexArray::bind()
{

}

void VertexArray::unbind()
{

}

bool VertexArray::isBound()
{

}