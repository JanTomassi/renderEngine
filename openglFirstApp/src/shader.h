#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/matrix.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assert.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class shader
{
private:
	unsigned int m_shader_id;
	std::vector<GLuint> compiledShaderId;

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
	shader() {
		m_shader_id = glCreateProgram();
	};

	~shader() {
		glDeleteProgram(m_shader_id);
	}

	void add(GLuint type, const std::string& src) {
		std::ifstream in(src);

		std::string file;

		if (in.is_open()) {

			while (!in.eof())
			{
				std::string c;
				std::getline(in, c);
				if (c != "") file += c;
				file += '\n';
			}
			file += '\n';

			unsigned int id = CompileShader(type, file);
			compiledShaderId.push_back(id);
		}
	}

	void compile() {
		for (size_t i = 0; i < compiledShaderId.size(); i++)
		{
			glAttachShader(m_shader_id, compiledShaderId[i]);
		}
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

		for (size_t i = 0; i < compiledShaderId.size(); i++)
		{
			glDetachShader(m_shader_id, compiledShaderId[i]);
		}
	}

	void useShader() {
		glUseProgram(m_shader_id);
	}

	unsigned int getUniLoc(const std::string& name) {
		return glGetUniformLocation(m_shader_id, name.c_str());
	}

	void SetUniform4f(const std::string& name, float a, float b, float c, float d) {
		glUniform4f(getUniLoc(name), a, b, c, d);
	}

	void SetUniformMat4f(const std::string& name, const glm::mat4& value) {
		glUniformMatrix4fv(getUniLoc(name), 1, GL_FALSE, glm::value_ptr(value));
	}

};

