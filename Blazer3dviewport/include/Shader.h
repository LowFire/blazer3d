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
		GLuint id = 0;
	};

	friend ShaderInfo;

private:
	GLuint m_program = 0;
	ShaderInfo m_vertex;
	ShaderInfo m_fragment;
	static GLuint s_current_program;

	std::string f_readSource(const std::string& path);
	GLuint f_compileShader(ShaderInfo shader);
	GLuint f_linkProgram(std::array<GLuint, 2> shader_objs);

public:
	Shader() = delete;
	Shader(std::array<ShaderInfo, 2> shaders);
	~Shader();

	inline void use() { glUseProgram(m_program); s_current_program = m_program; }
	bool isInUse();
};