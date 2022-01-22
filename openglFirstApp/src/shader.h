#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <iostream>

class shader
{
public:
	unsigned int m_shader_id;

	unsigned int CompileShader(unsigned int type, std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, NULL);
		glCompileShader(id);

		int res;
		glGetShaderiv(id, GL_COMPILE_STATUS, &res);
		if (res == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile: " << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

public:
	shader(std::string& vs_src, std::string& fs_src) {
		m_shader_id = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vs_src);
		assert(vs != 0);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fs_src);
		assert(fs != 0);

		glAttachShader(m_shader_id, vs);
		glAttachShader(m_shader_id, fs);
		glLinkProgram(m_shader_id);
		
		//Testo for linking error
		GLint program_linked;
		glGetProgramiv(m_shader_id, GL_LINK_STATUS, &program_linked);
		if (program_linked != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetProgramInfoLog(m_shader_id, 1024, &log_length, message);
			std::cout << "Error in linking:" << std::endl;
			std::cout << message << std::endl;
		}

		glValidateProgram(m_shader_id);

		glDeleteShader(vs);
		glDeleteShader(fs);
	};

	~shader() {
		glDeleteProgram(m_shader_id);
	}

	void useShader() { glUseProgram(m_shader_id); }
};

