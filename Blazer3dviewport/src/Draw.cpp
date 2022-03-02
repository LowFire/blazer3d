#include "Draw.h"

Draw::Draw() : m_origin(glm::vec3(0)), m_vert_count(3), position(glm::vec3(0)), 
	rotation(glm::vec3(0)), scale(glm::vec3(1))
{
	//Setup vertex array
	VertexArray::VertexAttribute pos{
	 0, 2, GL_FLOAT, GL_FALSE, 0, 0
	};
	m_arrays = VertexArray { pos };

	//Setup buffer
	m_buffer = Buffer{
		{ 0, sizeof(GLfloat) * 6, 0, GL_FLOAT }
	};
	auto data = std::make_shared<GLfloat>(new GLfloat[]{
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	});
	m_buffer.writeData(0, data);
}

void Draw::draw()
{
	m_arrays.bind();
	m_buffer.bind();
	glDrawArrays(GL_TRIANGLES, 0, m_vert_count);
}

void Draw::setBuffer(const Buffer& buffer)
{
	GLuint old = m_buffer.getOpenglName();
	glDeleteBuffers(1, &old);
	m_buffer = buffer;
}

Buffer Draw::getBuffer()
{
	return m_buffer;
}

void Draw::setVertexArray(const VertexArray& arrays)
{
	GLuint old = m_arrays.getOpenglName();
	glDeleteVertexArrays(1, &old);
	m_arrays = arrays;
}

VertexArray Draw::getVertexArray()
{
	return m_arrays;
}

int Draw::getVertCount()
{
	return m_vert_count;
}

void Draw::setOrigin(glm::vec3 origin)
{
	m_origin = origin;
}

glm::vec3 Draw::getOrigin()
{
	return m_origin;
}