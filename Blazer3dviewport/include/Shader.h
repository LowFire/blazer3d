#pragma once
#include <string>
#include <array>

#include <glad/glad.h>

namespace TestOpenglWrapperAPI
{
	class TestShader;
}

class Shader
{
	friend TestOpenglWrapperAPI::TestShader;
public:
	struct ShaderInfo
	{
		GLenum type;
		std::string filepath;
	};

private:
	GLuint m_program;
	ShaderInfo m_vertex;
	ShaderInfo m_fragment;
	static GLuint s_current_program;

public:
	Shader() = delete; //The default constructor is not allowed
	Shader(std::array<ShaderInfo, 2> shaders);

	void use();
};