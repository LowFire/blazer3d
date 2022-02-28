#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestOpenglWrapperAPI
{
	TEST_CLASS(TestShader)
	{
		TEST_CLASS_INITIALIZE(InitApplication)
		{
			glfwInit();

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

			//Create windows
			GLFWwindow* window = glfwCreateWindow(800, 640, "Test", NULL, NULL);

			if (window == nullptr) {
				std::cout << "Failed to create window" << std::endl;
			}

			glfwMakeContextCurrent(window);

			//Get opengl functions
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
			}

			glViewport(0, 0, 800, 640);
		}

		TEST_CLASS_CLEANUP(DestroyApplication)
		{
			glfwTerminate();
		}

		TEST_METHOD(testCompileAndLink)
		{
			Shader::ShaderInfo vertex{  GL_VERTEX_SHADER, "D:/Desktop/schoolwork/CSE499/blazer3d/Blazer3dviewport/shaders/testVertex.vert" };
			Shader::ShaderInfo fragment{  GL_FRAGMENT_SHADER, "D:/Desktop/schoolwork/CSE499/blazer3d/Blazer3dviewport/shaders/testFragment.frag" };

			std::array<Shader::ShaderInfo, 2> info = { vertex, fragment };
			Shader shader(info);

			//Test if the program id has been set
			Assert::IsTrue(shader.m_program != 0);

			//Test if the shader objects have been attached to the program
			GLint numShaders;
			GLuint shaders[2];
			glGetAttachedShaders(shader.m_program, 2, &numShaders, shaders);
			Assert::AreEqual(2, numShaders);

			//Test the compile status of the shaders
			GLint vertex_compile_status;
			GLint fragment_compile_status;
			glGetShaderiv(shaders[0], GL_COMPILE_STATUS, &vertex_compile_status);
			glGetShaderiv(shaders[1], GL_COMPILE_STATUS, &fragment_compile_status);

			Assert::AreEqual(GL_TRUE, vertex_compile_status);
			Assert::AreEqual(GL_TRUE, fragment_compile_status);

			//Test the program link status
			GLint program_link_status;
			glGetProgramiv(shader.m_program, GL_LINK_STATUS, &program_link_status);
			Assert::AreEqual(GL_TRUE, program_link_status);
		}

		TEST_METHOD(testUse)
		{
			Shader::ShaderInfo vertex{ GL_VERTEX_SHADER, "D:/Desktop/schoolwork/CSE499/blazer3d/Blazer3dviewport/shaders/testVertex.vert" };
			Shader::ShaderInfo fragment{ GL_FRAGMENT_SHADER, "D:/Desktop/schoolwork/CSE499/blazer3d/Blazer3dviewport/shaders/testFragment.frag" };

			std::array<Shader::ShaderInfo, 2> info = { vertex, fragment };
			Shader shader1(info);
			Shader shader2(info);

			shader1.use();
			Assert::IsTrue(shader1.isInUse());
			Assert::IsFalse(shader2.isInUse());
			Assert::AreEqual(Shader::s_current_program, shader1.m_program);

			shader2.use();
			Assert::IsTrue(shader2.isInUse());
			Assert::IsFalse(shader1.isInUse());
			Assert::AreEqual(Shader::s_current_program, shader2.m_program);
		}

		TEST_METHOD(testDestructor)
		{
			Shader::ShaderInfo vertex{ GL_VERTEX_SHADER, "D:/Desktop/schoolwork/CSE499/blazer3d/Blazer3dviewport/shaders/testVertex.vert" };
			Shader::ShaderInfo fragment{ GL_FRAGMENT_SHADER, "D:/Desktop/schoolwork/CSE499/blazer3d/Blazer3dviewport/shaders/testFragment.frag" };
			std::array<Shader::ShaderInfo, 2> info = { vertex, fragment };
			GLuint program;
			GLuint shader_objs[2];
			{
				Shader shader(info);
				program = shader.m_program;
				glGetAttachedShaders(program, 2, NULL, shader_objs);
				Assert::IsTrue(glIsProgram(program));
				Assert::IsTrue(glIsShader(shader_objs[0]));
				Assert::IsTrue(glIsShader(shader_objs[1]));
			}

			//The program and all attached shaders should be deleted
			Assert::IsFalse(glIsProgram(program));
			Assert::IsFalse(glIsShader(shader_objs[0]));
			Assert::IsFalse(glIsShader(shader_objs[1]));
		}
	};
}