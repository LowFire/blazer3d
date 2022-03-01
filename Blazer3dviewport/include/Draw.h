#pragma once
#include <glm\vec3.hpp>

#include "Buffer.h"
#include "VertexArray.h"

namespace TestOpenglWrapperAPI
{
	class TestDraw;
}

class Draw
{
	friend TestOpenglWrapperAPI::TestDraw;
private:
	VertexArray m_arrays;
	Buffer m_buffer;
	GLint m_vert_count;
	glm::vec3 m_origin;

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Draw();
	//Draw(const VertexArray& arrays, const Buffer& buffer);

	void draw();
	void setBuffer(const Buffer& buffer);
	Buffer getBuffer();
	void setVertexArray(const VertexArray& arrays);
	VertexArray getVertexArray();
	int getVertCount();
	void setOrigin(glm::vec3 origin);
	glm::vec3 getOrigin();
};