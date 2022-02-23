#include "Buffer.h"

GLuint Buffer::s_currently_bound_buf = 0;

Buffer::Buffer() : /*p_data((GLbyte*)nullptr),*/ m_total_size(0),
m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
{
	glCreateBuffers(1, &m_opengl_name);
	m_object_type = GL_BUFFER;
	setLabel(std::to_string(m_opengl_name));
};

Buffer::Buffer(std::initializer_list<DataBlockAttribute> l) :
	/*p_data((GLbyte*)nullptr),*/ m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
{
	glCreateBuffers(1, &m_opengl_name);
	m_object_type = GL_BUFFER;
	setLabel(std::to_string(m_opengl_name));

	//Allocate memory for buffer object using data block attributes.
	GLint mem_size = 0;
	for (auto b : l)
	{
		mem_size += b.size;
		auto new_entry = std::make_pair(b.index, b);
		m_data_attrib.insert(new_entry);
	}
	m_total_size = mem_size;
	glNamedBufferStorage(m_opengl_name, m_total_size, nullptr, m_usage);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_opengl_name);
}

void Buffer::bind()
{
	glBindBuffer(m_target, m_opengl_name);
	s_currently_bound_buf = m_opengl_name;
}

void Buffer::unbind()
{
	if (s_currently_bound_buf == m_opengl_name)
	{
		glBindBuffer(m_target, 0);
		s_currently_bound_buf = 0;
	}
}

bool Buffer::isBound()
{
	if (s_currently_bound_buf == m_opengl_name)
		return true;
	return false;
}

void Buffer::reset()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	s_currently_bound_buf = 0;
}