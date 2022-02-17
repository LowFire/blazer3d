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
	this->attribute_names = copy.attribute_names;
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
	glCreateVertexArrays(1, &opengl_name);
	label = std::to_string(opengl_name);
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());

	bind();
	for (auto a : l)
	{
		auto new_entry = std::make_pair(a.index, a);
		vertex_attributes.insert(new_entry);
		auto new_name = std::make_pair(a.name, a.index);
		attribute_names.insert(new_name);

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

void VertexArray::enableAttribute(const std::string& label)
{
	bind();
	GLuint index = attribute_names.at(label);
	glEnableVertexAttribArray(index);
	vertex_attributes.at(index).enabled = true;
	unbind();
}

//void VertexArray::enableAttribute(GLuint index)
//{
//	bind();
//	glEnableVertexAttribArray(index);
//
//	unbind();
//}

void VertexArray::disableAttribute(const std::string& label)
{
	bind();
	GLuint index = attribute_names.at(label);
	glDisableVertexAttribArray(index);
	vertex_attributes.at(index).enabled = false;
	unbind();
}

//void VertexArray::disableAttribute(GLuint index)
//{
//	bind();
//	glDisableVertexAttribArray(index);
//	unbind();
//}

void VertexArray::setLabel(std::string label)
{
	this->label = label;
	glObjectLabel(GL_VERTEX_ARRAY,
		opengl_name,
		B_NULL_TERMINATED,
		this->label.c_str());
}

void VertexArray::createAttribute(const std::string& name,
	GLuint index,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	void* offset)
{
	//Get a unique index.
	/*GLuint new_index = 0;
	while (!attribute_names.insert(new_index).second)
		new_index++;*/

	VertexArray::VertexAttribute new_attribute { name, index, size, type, normalized, stride, offset };
	auto new_entry = std::make_pair(index, new_attribute);
	vertex_attributes.insert(new_entry);
	auto new_name = std::make_pair(name, index);
	attribute_names.insert(new_name);

	//Set state for attribute in vao
	bind();
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	unbind();
}

void VertexArray::addAttributes(std::initializer_list<VertexArray::VertexAttribute> l)
{
	for (auto a : l)
	{
		if (!attribute_names.count(a.name) &&
			!vertex_attributes.count(a.index))
		{
			auto new_entry = std::make_pair(a.index, a);
			vertex_attributes.insert(new_entry);
			auto new_name = std::make_pair(a.name, a.index);
			attribute_names.insert(new_name);
		}
		else if (attribute_names.count(a.name))
		{
			a.index = attribute_names.at(a.name);
			vertex_attributes.erase(a.index);
			auto new_entry = std::make_pair(a.index, a);
			vertex_attributes.insert(new_entry);
		}
		else
		{
			auto old_name = vertex_attributes.at(a.index).name;
			attribute_names.erase(old_name);
			vertex_attributes.erase(a.index);
			auto new_entry = std::make_pair(a.index, a);
			vertex_attributes.insert(new_entry);
			auto new_name = std::make_pair(a.name, a.index);
			attribute_names.insert(new_name);
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
	if (!attribute_names.count(attrib.name) &&
		!vertex_attributes.count(attrib.index))
	{
		auto new_entry = std::make_pair(attrib.index, attrib);
		vertex_attributes.insert(new_entry);
		auto new_name = std::make_pair(attrib.name, attrib.index);
		attribute_names.insert(new_name);
	}
	else if (attribute_names.count(attrib.name))
	{
		attrib.index = attribute_names.at(attrib.name);
		vertex_attributes.erase(attrib.index);
		auto new_entry = std::make_pair(attrib.index, attrib);
		vertex_attributes.insert(new_entry);
	}
	else
	{
		auto old_name = vertex_attributes.at(attrib.index).name;
		attribute_names.erase(old_name);
		vertex_attributes.erase(attrib.index);
		auto new_entry = std::make_pair(attrib.index, attrib);
		vertex_attributes.insert(new_entry);
		auto new_name = std::make_pair(attrib.name, attrib.index);
		attribute_names.insert(new_name);
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

VertexArray::VertexAttribute VertexArray::getAttribute(const std::string& name)
{
	GLuint index = attribute_names.at(name);
	auto attrib = vertex_attributes.at(index);
	return attrib;
}

//VertexArray::VertexAttribute VertexArray::getAttribute(GLuint index)
//{
//	return { "0", 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0) };
//}

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
	//Insert attribute with new name
	GLuint index = attribute_names.at(name);
	VertexArray::VertexAttribute new_attrib = vertex_attributes.at(index);
	new_attrib.name = new_name;
	auto new_entry = std::make_pair(index, new_attrib);
	vertex_attributes.erase(index);
	vertex_attributes.insert(new_entry);

	//Update the name in attribute_names
	attribute_names.erase(name);
	auto new_attrib_name = std::make_pair(new_name, index);
	attribute_names.insert(new_attrib_name);
}

//void VertexArray::setAttributeName(GLuint index)
//{
//
//}

void VertexArray::setAttributeSize(const std::string& name, GLint size)
{
	bind();
	GLuint index = attribute_names.at(name);
	vertex_attributes.at(index).size = size;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}
//void VertexArray::setAttributeSize(GLuint index, GLint size)
//{
//
//}

void VertexArray::setAttributeNormalized(const std::string& name, GLboolean normalized)
{
	bind();
	GLuint index = attribute_names.at(name);
	vertex_attributes.at(index).normalized = normalized;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

//void VertexArray::setAttributeNormalized(GLuint index, GLboolean normalized)
//{
//
//}

void VertexArray::setAttributeType(const std::string& name, GLenum type)
{
	bind();
	GLuint index = attribute_names.at(name);
	vertex_attributes.at(index).type = type;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

//void VertexArray::setAttributeType(GLuint index, GLenum type)
//{
//
//}

void VertexArray::setAttributeOffset(const std::string& name, void* offset)
{
	bind();
	GLuint index = attribute_names.at(name);
	vertex_attributes.at(index).offset = offset;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

//void VertexArray::setAttributeOffset(GLuint index, GLint offset)
//{
//
//}

void VertexArray::setAttributeStride(const std::string& name, GLsizei stride)
{
	bind();
	GLuint index = attribute_names.at(name);
	vertex_attributes.at(index).stride = stride;
	glVertexAttribPointer(vertex_attributes.at(index).index,
		vertex_attributes.at(index).size,
		vertex_attributes.at(index).type,
		vertex_attributes.at(index).normalized,
		vertex_attributes.at(index).stride,
		vertex_attributes.at(index).offset);
	unbind();
}

//void VertexArray::setAttributeStride(GLuint index, GLsizei stride)
//{
//
//}