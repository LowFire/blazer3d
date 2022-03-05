#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Draw.h"

namespace TestOpenglWrapperAPI {
	class TestRender;
}

class Render
{
	friend TestOpenglWrapperAPI::TestRender;
private:
	static Render * p_instance;
	std::vector<Draw> m_draw_objects;
	Render() {};

public:
	static Render* getInstance()
	{
		if (p_instance == nullptr)
			p_instance = new Render;
		return p_instance;
	}

	void update(GLFWwindow* window);
	void setDrawObjects(std::vector<Draw> objects) {
		m_draw_objects = objects;
	}
};