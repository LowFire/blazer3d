#pragma once
#include <memory>
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
	std::shared_ptr<VertexArray> m_arrays;
	std::shared_ptr<Buffer> m_buffer;
	GLint m_vert_count;
	glm::vec3 m_origin;

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Draw();
	//Draw(const VertexArray& arrays, const Buffer& buffer);

	void draw();
	//void setBuffer(Buffer& buffer);
	std::shared_ptr<Buffer> getBuffer();
	//void setVertexArray(const VertexArray& arrays);
	std::shared_ptr<VertexArray> getVertexArray();
	int getVertCount();
	void setOrigin(glm::vec3 origin);
	glm::vec3 getOrigin();
};