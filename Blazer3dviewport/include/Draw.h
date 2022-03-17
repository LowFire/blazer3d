#pragma once
#include <memory>
#include <glm\vec3.hpp>

#include "VertexBuffer.h"
//#include "IndexBuffer.h"
#include "Shader.h"

namespace TestOpenglWrapperAPI
{
	class TestDraw;
}

class Draw abstract
{
	friend TestOpenglWrapperAPI::TestDraw;
private:
	//std::shared_ptr<VertexArray> m_arrays;
	std::shared_ptr<VertexBuffer> m_vertex;
	//std::shared_ptr<IndexBuffer> m_index;
	std::shared_ptr<Shader> m_shader;
	GLint m_vert_count;
	glm::vec3 m_origin;

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Draw();

	virtual void draw() abstract;

	void setBuffer(const std::shared_ptr<Buffer> buffer);
	std::shared_ptr<Buffer> getBuffer();
	void setVertexArray(const std::shared_ptr<VertexArray> arrays);
	std::shared_ptr<VertexArray> getVertexArray();
	int getVertCount();
	void setOrigin(glm::vec3 origin);
	glm::vec3 getOrigin();
	void setShader(const std::shared_ptr<Shader>& shader);
	std::shared_ptr<Shader> getShader();
};