#include "VertexArray.h"
#include "constants.h"

//Static variables
GLuint VertexArray::current_bound_vao = 0;

//Constructors
VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &opengl_name);
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
	glCreateVertexArrays(1, &opengl_name);
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
	glCreateVertexArrays(1, &opengl_name);
	this->label = std::to_string(opengl_name);
	this->vertex_attributes = copy.vertex_attributes;
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());

	bind();
	for (const auto& entry : vertex_attributes)
	{
		auto a = entry.second;

		//Set attributes
		glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.offset);
	}
	unbind();
}

VertexArray::VertexArray(std::initializer_list<VertexArray::VertexAttribute>l)
{
	glCreateVertexArrays(1, &opengl_name);
	label = std::to_string(opengl_name);
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());

	bind();
	for (const auto& a : l)
	{
		auto new_entry = std::make_pair(a.index, a);
		vertex_attributes.insert(new_entry);

		//Set attributes
		glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.offset);
	}
	unbind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &opengl_name);
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

void VertexArray::enableAttribute(GLuint index)
{
	bind();
	glEnableVertexAttribArray(index);
	vertex_attributes.at(index).enabled = true;
	unbind();
}

void VertexArray::disableAttribute(GLuint index)
{
	bind();
	glDisableVertexAttribArray(index);
	vertex_attributes.at(index).enabled = false;
	unbind();
}

void VertexArray::setLabel(const std::string& label)
{
	this->label = label;
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());
}

void VertexArray::createAttribute(GLuint index,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	void* offset)
{
	VertexArray::VertexAttribute new_attribute { index, size, type, normalized, stride, offset };
	auto new_entry = std::make_pair(index, new_attribute);
	addAttributes(new_attribute);
}

void VertexArray::addAttributes(std::initializer_list<VertexArray::VertexAttribute> l)
{
	for (const auto& a : l)
	{
		if (!vertex_attributes.count(a.index))
		{
			auto new_entry = std::make_pair(a.index, a);
			vertex_attributes.insert(new_entry);
		}
		else
		{
			vertex_attributes.erase(a.index);
			auto new_entry = std::make_pair(a.index, a);
			vertex_attributes.insert(new_entry);
		}

		//Update attribute pointer
		bind();
		glVertexAttribPointer(a.index, 
			a.size, 
			a.type, 
			a.normalized, 
			a.stride, 
			a.offset);
		unbind();
	}
}

void VertexArray::addAttributes(VertexArray::VertexAttribute attrib)
{
	if (!vertex_attributes.count(attrib.index))
	{
		auto new_entry = std::make_pair(attrib.index, attrib);
		vertex_attributes.insert(new_entry);
	}
	else
	{
		vertex_attributes.erase(attrib.index);
		auto new_entry = std::make_pair(attrib.index, attrib);
		vertex_attributes.insert(new_entry);
	}

	//Update attribute pointer
	bind();
	glVertexAttribPointer(attrib.index, 
		attrib.size, 
		attrib.type, 
		attrib.normalized, 
		attrib.stride, 
		attrib.offset);
	unbind();
}

VertexArray::VertexAttribute VertexArray::getAttribute(GLuint index)
{
		auto attrib = vertex_attributes.at(index);
		return attrib;
}

std::vector<VertexArray::VertexAttribute> VertexArray::getAllAttributes()
{
	std::vector<VertexAttribute> arr;
	for (const auto& a : vertex_attributes)
	{
		auto attrib = a.second;
		arr.push_back(attrib);
	}
	return arr;
}

void VertexArray::setAttributeSize(GLuint index, GLint size)
{
	bind();
	vertex_attributes.at(index).size = size;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeNormalized(GLuint index, GLboolean normalized)
{
	bind();
	vertex_attributes.at(index).normalized = normalized;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeType(GLuint index, GLenum type)
{
	bind();
	vertex_attributes.at(index).type = type;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeOffset(GLuint index, void* offset)
{
	bind();
	vertex_attributes.at(index).offset = offset;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeStride(GLuint index, GLsizei stride)
{
	bind();
	vertex_attributes.at(index).stride = stride;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}