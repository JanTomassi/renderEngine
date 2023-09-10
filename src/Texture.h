#pragma once
#include <GL/glew.h>
#include <vector>

struct tex_parameters
{
public:
	GLuint first;
	GLuint second;
};

class TexParameter
{
public:
	TexParameter() {};
	~TexParameter() {};

	void Push(GLuint first, GLuint second);

	inline std::vector<tex_parameters> Get() {
		return m_Elements;
	};

private:
	std::vector<tex_parameters> m_Elements;

};

class Texture : public TexParameter
{
public:
	GLuint m_tex;

	GLuint tex_type;
	int width, height;

	Texture(GLuint type, int width, int height);
	~Texture();

	void Bind();
	void UnBind();

	void setTexture(int level = 0);
	void resizeTexture(int width, int height, int level = 0);
	void BindImage(GLuint mode);

private:
	const GLuint genTexture();
};
