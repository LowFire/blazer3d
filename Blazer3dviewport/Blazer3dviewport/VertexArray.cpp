#include "VertexArray.h"
#include "constants.h"

//Static variables
GLuint VertexArray::m_current_bound_vao = 0;

//Constructors
VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_opengl_name);
	m_label = std::to_string(m_opengl_name);
	glObjectLabel(GL_VERTEX_ARRAY,
		m_opengl_name,
		B_NULL_TERMINATED,
		m_label.c_str());
	bind();
	unbind();
}

VertexArray::VertexArray(const std::string m_label)
{
	glCreateVertexArrays(1, &m_opengl_name);
	this->m_label = m_label;
	glObjectLabel(GL_VERTEX_ARRAY,
		m_opengl_name,
		B_NULL_TERMINATED,
		this->m_label.c_str());
	bind();
	unbind();
}

VertexArray::VertexArray(const VertexArray& copy)
{
	glCreateVertexArrays(1, &m_opengl_name);
	this->m_label = std::to_string(m_opengl_name);
	this->m_vertex_attributes = copy.m_vertex_attributes;
	glObjectLabel(GL_VERTEX_ARRAY,
		m_opengl_name,
		B_NULL_TERMINATED,
		this->m_label.c_str());

	bind();
	for (const auto& entry : m_vertex_attributes)
	{
		auto a = entry.second;

		//Set attributes
		glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.offset);
	}
	unbind();
}

VertexArray::VertexArray(std::initializer_list<VertexArray::VertexAttribute>l)
{
	glCreateVertexArrays(1, &m_opengl_name);
	m_label = std::to_string(m_opengl_name);
	glObjectLabel(GL_VERTEX_ARRAY,
		m_opengl_name,
		B_NULL_TERMINATED,
		this->m_label.c_str());

	bind();
	for (const auto& a : l)
	{
		auto new_entry = std::make_pair(a.index, a);
		m_vertex_attributes.insert(new_entry);

		//Set attributes
		glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.offset);
	}
	unbind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_opengl_name);
}

//Public methods
void VertexArray::bind()
{
	glBindVertexArray(m_opengl_name);
	m_current_bound_vao = m_opengl_name;
}

void VertexArray::unbind()
{
	if (m_current_bound_vao == m_opengl_name)
	{
		glBindVertexArray(0);
		m_current_bound_vao = 0;
	}
}

bool VertexArray::isBound()
{
	if (m_opengl_name == m_current_bound_vao)
		return true;
	return false;
}

void VertexArray::enableAttribute(GLuint index)
{
	bind();
	glEnableVertexAttribArray(index);
	m_vertex_attributes.at(index).enabled = true;
	unbind();
}

void VertexArray::disableAttribute(GLuint index)
{
	bind();
	glDisableVertexAttribArray(index);
	m_vertex_attributes.at(index).enabled = false;
	unbind();
}

void VertexArray::setLabel(const std::string& label)
{
	this->m_label = label;
	glObjectLabel(GL_VERTEX_ARRAY,
		m_opengl_name,
		B_NULL_TERMINATED,
		this->m_label.c_str());
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
		if (!m_vertex_attributes.count(a.index))
		{
			auto new_entry = std::make_pair(a.index, a);
			m_vertex_attributes.insert(new_entry);
		}
		else
		{
			m_vertex_attributes.erase(a.index);
			auto new_entry = std::make_pair(a.index, a);
			m_vertex_attributes.insert(new_entry);
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
	if (!m_vertex_attributes.count(attrib.index))
	{
		auto new_entry = std::make_pair(attrib.index, attrib);
		m_vertex_attributes.insert(new_entry);
	}
	else
	{
		m_vertex_attributes.erase(attrib.index);
		auto new_entry = std::make_pair(attrib.index, attrib);
		m_vertex_attributes.insert(new_entry);
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
		auto attrib = m_vertex_attributes.at(index);
		return attrib;
}

std::vector<VertexArray::VertexAttribute> VertexArray::getAllAttributes()
{
	std::vector<VertexAttribute> arr;
	for (const auto& a : m_vertex_attributes)
	{
		auto attrib = a.second;
		arr.push_back(attrib);
	}
	return arr;
}

void VertexArray::setAttributeSize(GLuint index, GLint size)
{
	bind();
	m_vertex_attributes.at(index).size = size;
	glVertexAttribPointer(m_vertex_attributes.at(index).index,
		m_vertex_attributes.at(index).size,
		m_vertex_attributes.at(index).type,
		m_vertex_attributes.at(index).normalized,
		m_vertex_attributes.at(index).stride,
		m_vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeNormalized(GLuint index, GLboolean normalized)
{
	bind();
	m_vertex_attributes.at(index).normalized = normalized;
	glVertexAttribPointer(m_vertex_attributes.at(index).index,
		m_vertex_attributes.at(index).size,
		m_vertex_attributes.at(index).type,
		m_vertex_attributes.at(index).normalized,
		m_vertex_attributes.at(index).stride,
		m_vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeType(GLuint index, GLenum type)
{
	bind();
	m_vertex_attributes.at(index).type = type;
	glVertexAttribPointer(m_vertex_attributes.at(index).index,
		m_vertex_attributes.at(index).size,
		m_vertex_attributes.at(index).type,
		m_vertex_attributes.at(index).normalized,
		m_vertex_attributes.at(index).stride,
		m_vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeOffset(GLuint index, void* offset)
{
	bind();
	m_vertex_attributes.at(index).offset = offset;
	glVertexAttribPointer(m_vertex_attributes.at(index).index,
		m_vertex_attributes.at(index).size,
		m_vertex_attributes.at(index).type,
		m_vertex_attributes.at(index).normalized,
		m_vertex_attributes.at(index).stride,
		m_vertex_attributes.at(index).offset);
	unbind();
}

void VertexArray::setAttributeStride(GLuint index, GLsizei stride)
{
	bind();
	m_vertex_attributes.at(index).stride = stride;
	glVertexAttribPointer(m_vertex_attributes.at(index).index,
		m_vertex_attributes.at(index).size,
		m_vertex_attributes.at(index).type,
		m_vertex_attributes.at(index).normalized,
		m_vertex_attributes.at(index).stride,
		m_vertex_attributes.at(index).offset);
	unbind();
}