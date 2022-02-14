#include "VertexArray.h"
#include "constants.h"

//Constructors
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &opengl_name);
	label = std::to_string(opengl_name);
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		label.c_str());
	bind();
	unbind();
}

VertexArray::VertexArray(const std::string label)
{
	glGenVertexArrays(1, &opengl_name);
	this->label = label;
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());
	bind();
	unbind();
}

VertexArray::VertexArray(const VertexArray& copy)
{
	glGenVertexArrays(1, &opengl_name);
	this->label = std::to_string(opengl_name);
	this->attribute_indexes = copy.attribute_indexes;
	this->vertex_attributes = copy.vertex_attributes;
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());

	bind();
	for (auto entry : vertex_attributes)
	{
		auto a = entry.second;

		//Set attributes
		glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.offset);
	}
	unbind();
}

VertexArray::VertexArray(std::initializer_list<VertexArray::VertexAttribute>l)
{
	glGenVertexArrays(1, &opengl_name);
	label = std::to_string(opengl_name);
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());

	bind();
	for (auto a : l)
	{
		auto new_entry = std::make_pair(a.name, a);
		vertex_attributes.insert(new_entry);
		attribute_indexes.push_back(a.index);

		//Set attributes
		glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.offset);
	}
	unbind();
}

VertexArray::~VertexArray()
{

}

//Public methods
void VertexArray::bind()
{
	glBindVertexArray(opengl_name);
	current_bound_vao = opengl_name;
}

void VertexArray::unbind()
{
	if (current_bound_vao == opengl_name)
	{
		glBindVertexArray(0);
		current_bound_vao = 0;
	}
}

bool VertexArray::isBound()
{
	if (opengl_name == current_bound_vao)
		return true;
	return false;
}

void VertexArray::enableAttribute(const std::string& label)
{
	bind();
	glEnableVertexAttribArray(vertex_attributes.at(label).index);
	unbind();
}

void VertexArray::enableAttribute(GLuint index)
{
	bind();
	glEnableVertexAttribArray(index);
	unbind();
}

void VertexArray::disableAttribute(const std::string& label)
{
	bind();
	glDisableVertexAttribArray(vertex_attributes.at(label).index);
	unbind();
}

void VertexArray::disableAttribute(GLuint index)
{
	bind();
	glDisableVertexAttribArray(index);
	unbind();
}

void VertexArray::setLabel(std::string label)
{
	this->label = label;
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());
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