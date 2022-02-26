#include <algorithm>
#include <fstream>
#include <vector>

#include <iostream>

#include "Shader.h"

GLuint Shader::s_current_program = 0;

std::string Shader::f_readSource(const std::string& path)
{
	std::ifstream in(path, std::ios_base::ate);
	if (in.fail())
	{
		std::cout << "Failed to open filepath: " << path << '\n';
		return "";
	}
	auto len = in.tellg();
	in.seekg(std::ios_base::beg);

	std::vector<char> buf;
	buf.resize(static_cast<size_t>(len));
	in.read(buf.data(), len);

	auto success = !in.fail() ;
	if (!success)
	{
		std::cout << "Error: Failed to read file: " << path << '\n';
		char buffer[80];
		std::cout << strerror_s(buffer, 80, NULL);
	}
	in.close();
	return std::string(buf.data());
}

GLuint Shader::f_compileShader(ShaderInfo shader)
{
	GLuint shader_id = glCreateShader(shader.type);
	std::string str = f_readSource(shader.filepath);
	const GLchar* source[1];
	source[0] = str.c_str();
	GLint length = str.size();
	glShaderSource(shader_id, 1, source, &length);

	glCompileShader(shader_id);
	GLint success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar log[2048];
		glGetShaderInfoLog(shader_id, 2048, NULL, log);
		std::cout << "Error: failed to compile " << shader.filepath << "!\n";
		std::cout << log << '\n';
		return 0;
	}

	return shader_id;
}

GLuint Shader::f_linkProgram(std::array<GLuint, 2> shader_objs)
{
	GLuint new_program = glCreateProgram();
	for (GLuint id : shader_objs)
		glAttachShader(new_program, id);

	glLinkProgram(new_program);

	GLint success;
	glGetProgramiv(new_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar log[2048];
		glGetProgramInfoLog(new_program, 2048, NULL, log);
		std::cout << "Error:: failed to link shader program!\n";
		std::cout << log << '\n';
		return 0;
	}
	return new_program;
}

Shader::Shader(std::array<ShaderInfo, 2> shaders)
{
	//Get vertex shader
	auto it = std::find_if(shaders.begin(), shaders.end(), [](const auto& shader) {
		if (shader.type == GL_VERTEX_SHADER)
			return true;
		return false;
		});

	if (it != shaders.end())
	{
		m_vertex = *it;
	}
	else {
		std::cout << "Error: no vertex shader was found!\n";
		return;
	};

	//Get fragment shader
	it = std::find_if(shaders.begin(), shaders.end(), [](const auto& shader) {
		if (shader.type == GL_FRAGMENT_SHADER)
			return true;
		return false;
		});

	if (it != shaders.end())
	{
		m_fragment = *it;
	}
	else {
		std::cout << "Error: no fragment shader was found!\n";
		return;
	};

	GLuint vert_obj = f_compileShader(m_vertex);
	GLuint frag_obj = f_compileShader(m_fragment);
	std::array<GLuint, 2> shader_ids{ vert_obj, frag_obj };
	m_program = f_linkProgram(shader_ids);
}

bool Shader::isInUse()
{
	if (s_current_program == m_program)
		return true;
	return false;
}