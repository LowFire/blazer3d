#include "Render.h"

Render* Render::p_instance = nullptr;

void Render::update(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& d : m_draw_objects)
	{
		d.draw();
	}

	glfwSwapBuffers(window);
}