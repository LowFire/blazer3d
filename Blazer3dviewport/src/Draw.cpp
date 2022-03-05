#include "Draw.h"

/*NOTE: The default constructor should not initialize the buffer and vertex array
it points to. Both references should be null on construction.*/
Draw::Draw() : m_origin(glm::vec3(0)), m_vert_count(3), position(glm::vec3(0)), 
	rotation(glm::vec3(0)), scale(glm::vec3(1))
{
	//Setup buffer first
	m_buffer = std::make_shared<Buffer>(new Buffer);
	m_buffer->initData(std::vector<Buffer::DataBlockAttribute> {
		{ 0, sizeof(GLfloat) * 6, 0, GL_FLOAT }
	});

	auto data = std::shared_ptr<GLfloat>(new GLfloat[]{
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
		});
	m_buffer->writeData(0, data);
	m_buffer->bind();

	//Setup vertex array
	m_arrays = std::make_shared<VertexArray>(new VertexArray);
	VertexArray::VertexAttribute pos{
	 0, 2, GL_FLOAT, GL_FALSE, 0, 0
	};
	m_arrays->addAttributes(pos);

	m_arrays->enableAttribute(0);
}

void Draw::draw()
{
	m_arrays->bind();
	m_buffer->bind();
	glDrawArrays(GL_TRIANGLES, 0, m_vert_count);
}

//void Draw::setBuffer(Buffer& buffer)
//{
//	GLuint old = m_buffer->getOpenglName();
//	glDeleteBuffers(1, &old);
//	m_buffer = buffer;
//}

std::shared_ptr<Buffer> Draw::getBuffer()
{
	return m_buffer;
}

//void Draw::setVertexArray(const VertexArray& arrays)
//{
//	m_arrays = arrays;
//}

std::shared_ptr<VertexArray> Draw::getVertexArray()
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