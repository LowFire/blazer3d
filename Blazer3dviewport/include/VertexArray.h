#pragma once

#include <vector>
#include <map>
#include <string>

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
		const void* offset;
	};

private:
	GLuint opengl_name;
	std::string label;
	std::map<std::string, VertexAttribute> vertex_attributes;
	std::vector<GLuint> attribute_indexes;

public:
	VertexArray();
	VertexArray(const std::string label);
	VertexArray(const VertexArray& copy);
	VertexArray(std::initializer_list<VertexArray::VertexAttribute>l);

};