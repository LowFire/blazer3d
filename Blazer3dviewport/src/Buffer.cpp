#include "Buffer.h"

Buffer::Buffer() : p_data((GLbyte*)nullptr), m_total_size(0),
m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
{
	glCreateBuffers(1, &m_opengl_name);
};

Buffer::Buffer(std::initializer_list<DataBlockAttribute> l) :
	p_data((GLbyte*)nullptr), m_target(GL_ARRAY_BUFFER), m_usage(GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
{
	glCreateBuffers(1, &m_opengl_name);

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

//template <typename T>
void Buffer::writeData(int data_index, std::shared_ptr<GLbyte> data)
{
	const auto& block = m_data_attrib.at(data_index);
	p_data = (GLbyte*)glMapNamedBufferRange(m_opengl_name,
		block.offset,
		block.size,
		GL_WRITE_ONLY);

	//Write data into the buffer
	//int count = block.size / sizeof(T);
	for (int i = 0; i < block.size; i++)
	{
		p_data[i] = data.get()[i];
	}

	glFlushMappedNamedBufferRange(m_opengl_name, block.offset, block.size);
	glUnmapNamedBuffer(m_opengl_name);
	p_data = nullptr;
}

template <typename T>
std::shared_ptr<T> Buffer::readData(int data_index) //TODO: Return a pointer of the type of data stored in the block.
{
	const auto& block = m_data_attrib.at(data_index);
	p_data = (GLbyte*)glMapNamedBufferRange(m_opengl_name,
		block.offset,
		block.size,
		GL_READ_ONLY);

	//Allocate memory to store data.
	auto readData = std::make_shared<T>(new T[]);
}