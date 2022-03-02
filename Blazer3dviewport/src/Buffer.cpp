#include "Buffer.h"
#include "Type.h"

GLuint Buffer::s_currently_bound_buf = 0;

Buffer::Buffer() : m_total_size(0),
m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
{
	glCreateBuffers(1, &m_opengl_name);
	m_object_type = GL_BUFFER;
	setLabel(std::to_string(m_opengl_name));
};

Buffer::Buffer(std::initializer_list<DataBlockAttribute> l) :
	m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
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
	m_is_initialized = true;
}

Buffer::Buffer(Buffer& rhs) :
	m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT | GL_MAP_WRITE_BIT)
{
	glCreateBuffers(1, &m_opengl_name);
	m_object_type = GL_BUFFER;
	setLabel(std::to_string(m_opengl_name));

	//Copy over data blocks
	m_data_attrib = rhs.m_data_attrib;
	
	//Get the total size
	GLint mem_size = 0;
	for (const auto& b : m_data_attrib)
	{
		mem_size += b.second.size;
	}
	m_total_size = mem_size;
	glNamedBufferStorage(m_opengl_name, m_total_size, nullptr, m_usage);

	//Copy data over
	for (const auto& b : m_data_attrib)
	{
		auto data = rhs.readData<GLbyte>(b.first);
		writeData(b.first, data);
	}

	m_is_initialized = true;
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

void Buffer::initData(std::vector<DataBlockAttribute> data_blocks)
{
	if (!m_is_initialized)
	{
		GLint mem_size = 0;
		for (const auto& b : data_blocks)
		{
			mem_size += b.size;
			auto new_entry = std::make_pair(b.index, b);
			m_data_attrib.insert(new_entry);
		}
		m_total_size = mem_size;
		glNamedBufferStorage(m_opengl_name, m_total_size, nullptr, m_usage);
		m_is_initialized = true;
	}
}

int Buffer::getDataBlockCount(int index)
{
	auto it = m_data_attrib.find(index);
	if (it != m_data_attrib.end())
	{
		auto elem = it->second;
		return static_cast<int>(elem.size / getSizeOf(elem.type));
	}
	return -1;
}

GLsizeiptr Buffer::getDataBlockSize(int index)
{
	auto it = m_data_attrib.find(index);
	if (it != m_data_attrib.end())
	{
		auto elem = it->second;
		return elem.size;
	}
	return -1;
}

GLenum Buffer::getDataBlockType(int index)
{
	auto it = m_data_attrib.find(index);
	if (it != m_data_attrib.end())
	{
		auto elem = it->second;
		return elem.type;
	}
	return -1;
}

GLintptr Buffer::getDataBlockOffset(int index)
{
	auto it = m_data_attrib.find(index);
	if (it != m_data_attrib.end())
	{
		auto elem = it->second;
		return elem.offset;
	}
	return -1;
}

//Buffer& Buffer::operator = (const Buffer& rhs)
//{
//
//}