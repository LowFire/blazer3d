#include "VertexArray.h"

//Constructors
VertexArray::VertexArray()
{

}

VertexArray::VertexArray(const std::string label)
{

}

VertexArray::VertexArray(const VertexArray& copy)
{

}

VertexArray::VertexArray(std::initializer_list<VertexArray::VertexAttribute>l)
{

}

VertexArray::~VertexArray()
{

}

//Public methods
void VertexArray::bind()
{
	glBindVertexArray(opengl_name);
}

void VertexArray::unbind()
{

}

bool VertexArray::isBound()
{
	return false;
}

void VertexArray::enableAttribute(const std::string& label)
{

}

void VertexArray::enableAttribute(GLuint index)
{

}

void VertexArray::disableAttribute(const std::string& label)
{

}

void VertexArray::disableAttribute(GLuint index)
{

}

void VertexArray::setLabel(std::string label)
{

}

void VertexArray::createAttribute(const std::string& name,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	void* offset)
{

}

void VertexArray::addAttributes()
{

}

VertexArray::VertexAttribute VertexArray::getAttribute(const std::string& name)
{
	return { "0", 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0) };
}

VertexArray::VertexAttribute VertexArray::getAttribute(GLuint index)
{
	return { "0", 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0) };
}

template <int size>
std::array<VertexArray::VertexAttribute, size> VertexArray::getAllAttributes()
{
	return std::array<VertexArray::VertexAttribute, 1>(
		{ "0", 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0) }
	);
}

void VertexArray::setAttributeName(const std::string& name,
	const std::string& new_name)
{

}

void VertexArray::setAttributeName(GLuint index)
{

}

void VertexArray::setAttributeSize(const std::string& name, GLint size)
{

}
void VertexArray::setAttributeSize(GLuint index, GLint size)
{

}

void VertexArray::setAttributeNormalized(const std::string& name, GLboolean normalized)
{

}

void VertexArray::setAttributeNormalized(GLuint index, GLboolean normalized)
{

}

void VertexArray::setAttributeType(const std::string& name, GLenum type)
{

}

void VertexArray::setAttributeType(GLuint index, GLenum type)
{

}

void VertexArray::setAttributeOffset(const std::string& name, GLint offset)
{

}

void VertexArray::setAttributeOffset(GLuint index, GLint offset)
{

}

void VertexArray::setAttributeStride(const std::string& name, GLsizei stride)
{

}

void VertexArray::setAttributeStride(GLuint index, GLsizei stride)
{

}