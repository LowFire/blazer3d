#include "IndexBuffer.h"

GLuint IndexBuffer::s_currently_bound_ebo = 0;

IndexBuffer::IndexBuffer() : Buffer()
{
	m_target = GL_ELEMENT_ARRAY_BUFFER;
	m_indicies_count = 0;
}

IndexBuffer::IndexBuffer(std::initializer_list<GLuint> l) : Buffer({
	DataBlockAttribute { 0, static_cast<GLsizeiptr>(sizeof(GLuint) * l.size()), 0, GL_UNSIGNED_INT} })
{
	m_target = GL_ELEMENT_ARRAY_BUFFER;
	m_indicies_count = l.size();

	setIndicies(l);
}

void IndexBuffer::reset()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	s_currently_bound_ebo = 0;
}

void IndexBuffer::bind()
{
	glBindBuffer(m_target, m_opengl_name);
	s_currently_bound_ebo = m_opengl_name;
}

void IndexBuffer::unbind()
{
	if (s_currently_bound_ebo == m_opengl_name)
	{
		glBindBuffer(m_target, 0);
		s_currently_bound_ebo = 0;
	}
}

bool IndexBuffer::isBound()
{
	if (s_currently_bound_ebo == m_opengl_name)
		return true;
	return false;
}

void IndexBuffer::setIndicies(std::vector<GLuint> indicies)
{

	if (!m_is_initialized)
	{
		initData({ DataBlockAttribute{ 
			0, 
			static_cast<GLsizeiptr>(sizeof(GLuint) * indicies.size()), 
			0,
			GL_UNSIGNED_INT }});

		m_indicies_count = indicies.size();

		std::shared_ptr<GLuint> data(new GLuint[indicies.size()]);
		for (int i = 0; i < indicies.size(); i++)
			data.get()[i] = indicies.at(i);
		writeData<GLuint>(0, data);
	}
	else
	{
		if (m_indicies_count != indicies.size())
		{
			std::cout << "WARNING: Failed to set indicies in index buffer: " + m_label +
				". Invalid number of indicies provided";
			return;
		}

		std::shared_ptr<GLuint> data(new GLuint[indicies.size()]);
		for (int i = 0; i < indicies.size(); i++)
			data.get()[i] = indicies.at(i);
		writeData<GLuint>(0, data);
	}
}

std::vector<GLuint> IndexBuffer::getIndicies()
{
	auto data = readData<GLuint>(0);

	std::vector<GLuint> indicies;
	for (int i = 0; i < m_indicies_count; i++)
		indicies.push_back(data.get()[i]);

	return indicies;
}