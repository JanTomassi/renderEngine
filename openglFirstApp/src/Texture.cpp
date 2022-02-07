#include "Texture.h"
#include "Debug.h"

Texture::Texture(GLuint t, int w, int h) : m_tex(genTexture()), tex_type(t), width(w), height(h) {}

Texture::~Texture() { GLCALL(glDeleteTextures(1, &m_tex)); }

const GLuint Texture::genTexture() {
	GLuint tex_pos;
	GLCALL(glGenTextures(1, &tex_pos));
	return tex_pos;
}

void Texture::Bind() {
	GLCALL(glActiveTexture(GL_TEXTURE0));
	GLCALL(glBindTexture(tex_type, m_tex));
}

void Texture::BindImage(GLuint mode) {
	GLCALL(glBindImageTexture(0, m_tex, 0, GL_FALSE, 0, mode, GL_RGBA32F));
}

void Texture::UnBind() {
	GLCALL(glBindTexture(tex_type, 0));
}

void Texture::setTexture(int level) {
	Bind();

	for (const auto& tp : Get()) {
		GLCALL(glTexParameteri(tex_type, tp.first, tp.second));
	}

	GLCALL(glTexImage2D(tex_type, level, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL));
	UnBind();
}

void Texture::resizeTexture(int w, int h, int level) {
	width = w; height = h;
	GLCALL(glTexImage2D(tex_type, level, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL));
}

// Texture Parameter

void TexParameter::Push(GLuint first, GLuint second) {
	m_Elements.push_back(tex_parameters{ first,second });
}
