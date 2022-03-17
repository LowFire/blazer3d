#include "VertexBuffer.h"

GLuint VertexBuffer::s_currently_bound_vbo = 0;

VertexBuffer::VertexBuffer() : Buffer()
{
	m_target = GL_ARRAY_BUFFER;
}

VertexBuffer::VertexBuffer(std::initializer_list<DataBlockAttribute> l) : Buffer(l)
{
	m_target = GL_ARRAY_BUFFER;
	glBindBuffer(m_target, m_opengl_name);
}

VertexBuffer::VertexBuffer(std::initializer_list<DataBlockAttribute> l,
	std::initializer_list<VertexArray::VertexAttribute> arrays) : Buffer(l)
{
	m_target = GL_ARRAY_BUFFER;
	glBindBuffer(m_target, m_opengl_name);
	m_arrays = std::make_shared<VertexArray>();

	m_arrays->addAttributes(arrays);
}

void VertexBuffer::reset()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	s_currently_bound_vbo = 0;
}

std::shared_ptr<VertexArray> VertexBuffer::getVertexArray()
{
	return m_arrays;
}

void VertexBuffer::setVertexArray(std::shared_ptr<VertexArray> arr)
{
	m_arrays = arr;
}

void VertexBuffer::bind()
{
	glBindBuffer(m_target, m_opengl_name);
	s_currently_bound_vbo = m_opengl_name;
}

void VertexBuffer::unbind()
{
	if (s_currently_bound_vbo == m_opengl_name)
	{
		glBindBuffer(m_target, 0);
		s_currently_bound_vbo = 0;
	}
}

bool VertexBuffer::isBound()
{
	if (s_currently_bound_vbo == m_opengl_name)
		return true;
	return false;
}

void VertexBuffer::makeVertexArray(std::initializer_list<VertexArray::VertexAttribute> a)
{
	m_arrays.reset();
	m_arrays = std::make_shared<VertexArray>(a);
}