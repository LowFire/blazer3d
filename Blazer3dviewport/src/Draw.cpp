#include "Draw.h"

/*NOTE: The default constructor should not initialize the buffer and vertex array
it points to. Both references should be null on construction.*/
Draw::Draw() : m_origin(glm::vec3(0)), m_vert_count(3), position(glm::vec3(0)), 
	rotation(glm::vec3(0)), scale(glm::vec3(1))
{
	////Setup buffer first
	//m_buffer = std::make_shared<Buffer>();
	//m_buffer->initData(std::vector<Buffer::DataBlockAttribute> {
	//	{ 0, sizeof(GLfloat) * 6, 0, GL_FLOAT },
	//	{ 1, sizeof(GLfloat) * 9, sizeof(GLfloat) * 6, GL_FLOAT }
	//});

	//auto pos = std::shared_ptr<GLfloat>(new GLfloat[]{
	//	0.0f, 0.5f,
	//	0.5f, -0.5f,
	//	-0.5f, -0.5f
	//	});

	//auto color = std::shared_ptr<GLfloat>(new GLfloat[]{
	//	1.0f, 0.0, 0.0f,
	//	0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f
	//});
	//m_buffer->writeData(0, pos);
	//m_buffer->writeData(1, color);
	//m_buffer->bind();

	//Setup vertex array
	m_arrays = std::make_shared<VertexArray>();
	VertexArray::VertexAttribute pos_attrib{ 0, 2, GL_FLOAT, GL_FALSE, 0, 0 };
	VertexArray::VertexAttribute color_attrib{ 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * 6) };
	m_arrays->addAttributes({ pos_attrib, color_attrib });

	//Create and compile shader
	Shader::ShaderInfo vert{ GL_VERTEX_SHADER, "../shaders/testVertex.vert" };
	Shader::ShaderInfo frag { GL_FRAGMENT_SHADER, "../shaders/testFragment.frag" };
	std::array<Shader::ShaderInfo, 2> shaders{ vert, frag };
	m_shader = std::make_shared<Shader>(shaders);

	m_arrays->enableAttribute(0);
	m_arrays->enableAttribute(1);
}

void Draw::draw()
{
	m_arrays->bind();
	m_buffer->bind();
	m_shader->use();
	glDrawArrays(GL_TRIANGLES, 0, m_vert_count);
}

//void Draw::setBuffer(Buffer& buffer)
//{
//	GLuint old = m_buffer->getOpenglName();
//	glDeleteBuffers(1, &old);
//	m_buffer = buffer;
//}

//std::shared_ptr<Buffer> Draw::getBuffer()
//{
//	return m_buffer;
//}

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

void Draw::setShader(const std::shared_ptr<Shader>& shader)
{
	m_shader = shader;
}

const std::shared_ptr<Shader>& Draw::getShader()
{
	return m_shader;
}