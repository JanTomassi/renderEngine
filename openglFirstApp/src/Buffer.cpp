#include "Buffer.h"
#include "Debug.h"

glclass::Buffer::Buffer()
{
	GLCALL(glGenBuffers(1, &m_RenderId));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderId));
}

void glclass::Buffer::SetData(const void* data, unsigned int size) {
	Bind();
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

glclass::Buffer::~Buffer()
{
	GLCALL(glDeleteBuffers(1, &m_RenderId));
}

void glclass::Buffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderId));
}

void glclass::Buffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
