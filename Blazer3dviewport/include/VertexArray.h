#pragma once

#include <unordered_map>
#include <string>
#include <array>

#include <glad/glad.h>

namespace TestOpenglWrapperAPI {
	class TestVertexArray;
}

class VertexArray {
	friend TestOpenglWrapperAPI::TestVertexArray;
public:
	struct VertexAttribute {
		std::string name;
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		void* offset;
		bool enabled = false;
	};

private:
	GLuint opengl_name;
	std::string label;
	std::unordered_map<GLuint, VertexAttribute> vertex_attributes;
	std::unordered_map<std::string, GLuint> attribute_names;
	static GLuint current_bound_vao;

public:
	//Constructors
	VertexArray();
	VertexArray(const std::string label);
	VertexArray(const VertexArray& copy);
	VertexArray(std::initializer_list<VertexArray::VertexAttribute>l);
	~VertexArray();

	//Public methods
	void bind();
	void unbind();
	bool isBound();

	void enableAttribute(const std::string& label);
	//void enableAttribute(GLuint index);
	void disableAttribute(const std::string& label);
	//void disableAttribute(GLuint index);

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

	//template<typename T>
	//static void setGenericAttribute(const std::string& label, T value)
	//{
	//	glVertexAttrib3f(vertex_attributes.at(label).index,
	//		value, value, value);
	//}

	//template<typename T>
	//static void setGenericAttribute(const std::string& label, T value[])
	//{
	//	int size = sizeof(value) / sizeof(T);
	//	switch (size)
	//	{
	//	case 1:
	//		glVertexAttrib1f(vertex_attributes.at(label).index, value[0]);
	//	case 2:
	//		glVertexAttrib2f(vertex_attributes.at(label).index, value[0], value[1]);
	//	case 3:
	//		glVertexAttrib3f(vertex_attributes.at(label).index, value[0], value[1], value[2]);
	//	case 4:
	//		glVertexAttrib4f(vertex_attributes.at(label).index, value[0], value[1], value[2], value[3]);
	//	}
	//}

	//template<typename T>
	//static void setGenericAttribute(const std::string& label,
	//	std::initializer_list<T> l)
	//{
	//	auto it = l.begin();
	//	switch (l.size())
	//	{
	//	case 1:
	//		glVertexAttrib1f(vertex_attributes.at(label).index, *it);
	//	case 2:
	//		glVertexAttrib2f(vertex_attributes.at(label).index, *it, *(it + 1));
	//	case 3:
	//		glVertexAttrib3f(vertex_attributes.at(label).index, *it, *(it + 1), *(it + 2));
	//	case 4:
	//		glVertexAttrib4f(vertex_attributes.at(label).index, *it, *(it + 1), *(it + 2), *(it + 3));
	//	}
	//}

	GLuint getOpenglName() { return opengl_name; };
	std::string getLabel() { return label; };
	void setLabel(std::string label);

	void createAttribute(const std::string& name,
		GLuint index,
		GLint size,
		GLenum type,
		GLboolean normalized,
		GLsizei stride,
		void* offset);

	void addAttributes(std::initializer_list<VertexAttribute> l);
	void addAttributes(VertexAttribute attrib);

	VertexAttribute getAttribute(const std::string& name);
	//VertexAttribute getAttribute(GLuint index);
	template <int size>
	std::array<VertexAttribute, size> getAllAttributes();

	void setAttributeName(const std::string& name, 
		const std::string& new_name);
	//void setAttributeName(GLuint index);

	void setAttributeSize(const std::string& name, GLint size);
	//void setAttributeSize(GLuint index, GLint size);

	void setAttributeNormalized(const std::string& name, GLboolean normalized);
	//void setAttributeNormalized(GLuint index, GLboolean normalized);

	void setAttributeType(const std::string& name, GLenum type);
	//void setAttributeType(GLuint index, GLenum type);

	void setAttributeOffset(const std::string& name, void* offset);
	//void setAttributeOffset(GLuint index, GLint offset);

	void setAttributeStride(const std::string& name, GLsizei stride);
	//void setAttributeStride(GLuint index, GLsizei stride);
};