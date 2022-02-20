#pragma once
#include <string>

#include <glad/glad.h>

#include "constants.h"

class OpenglObject {
protected:
	GLuint m_opengl_name;
	std::string m_label;
	GLenum m_object_type;

public:
	virtual void bind() = 0;
	virtual void unbind() = 0;

	GLuint getOpenglName() { return m_opengl_name; }
	std::string getLabel() { return m_label; }

	void setLabel(const std::string& label) {
		this->m_label = label;
		glObjectLabel(m_object_type,
			m_opengl_name,
			B_NULL_TERMINATED,
			this->m_label.c_str());
	}

	GLenum getObjectType() { return m_object_type; }
};