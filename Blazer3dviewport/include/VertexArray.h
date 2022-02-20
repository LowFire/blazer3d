#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "OpenglObject.h"

namespace TestOpenglWrapperAPI {
	class TestVertexArray;
}

class VertexArray : public OpenglObject {
	friend TestOpenglWrapperAPI::TestVertexArray;
public:
	struct VertexAttribute {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		void* offset;
		bool enabled = false;
	};

private:
	std::unordered_map<GLuint, VertexAttribute> m_vertex_attributes;
	static GLuint m_current_bound_vao;

public:
	//Constructors
	VertexArray();
	VertexArray(const std::string label);
	VertexArray(const VertexArray& copy);
	VertexArray(std::initializer_list<VertexArray::VertexAttribute>l);
	~VertexArray();

	//Public methods
	virtual void bind() override;
	virtual void unbind() override;
	static void reset();
	bool isBound();

	void enableAttribute(GLuint index);
	void disableAttribute(GLuint index);

	template<typename T>
	static void setGenericAttribute(const GLuint index, T value)
	{
		glVertexAttrib3f(index, value, value, value);
	}	
	
	template<typename T>
	static void setGenericAttribute(const GLuint index, T value[])
	{
		int size = sizeof(value) / sizeof(T);
		switch (size)
		{
		case 1:
			glVertexAttrib1f(index, value[0]);
		case 2:
			glVertexAttrib2f(index, value[0], value[1]);
		case 3:
			glVertexAttrib3f(index, value[0], value[1], value[2]);
		case 4:
			glVertexAttrib4f(index, value[0], value[1], value[2], value[3]);
		}
	}

	template<typename T>
	static void setGenericAttribute(const GLuint index,
		std::initializer_list<T> l)
	{
		auto it = l.begin();
		switch (l.size())
		{
		case 1:
			glVertexAttrib1f(index, *it);
		case 2:
			glVertexAttrib2f(index, *it, *(it + 1));
		case 3:
			glVertexAttrib3f(index, *it, *(it + 1), *(it + 2));
		case 4:
			glVertexAttrib4f(index, *it, *(it + 1), *(it + 2), *(it + 3));
		}
	}

	void createAttribute(GLuint index,
		GLint size,
		GLenum type,
		GLboolean normalized,
		GLsizei stride,
		void* offset);

	void addAttributes(std::initializer_list<VertexAttribute> l);
	void addAttributes(VertexAttribute attrib);

	VertexAttribute getAttribute(GLuint index);

	std::vector<VertexAttribute> getAllAttributes();

	void setAttributeSize(GLuint index, GLint size);

	void setAttributeNormalized(GLuint index, GLboolean normalized);

	void setAttributeType(GLuint index, GLenum type);

	void setAttributeOffset(GLuint index, void* offset);

	void setAttributeStride(GLuint index, GLsizei stride);
};