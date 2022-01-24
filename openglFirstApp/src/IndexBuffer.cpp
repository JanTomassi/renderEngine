#include "IndexBuffer.h"
#include "Debug.h"
#include <assert.h>

glclass::IndexBuffer::IndexBuffer()
{
	assert(sizeof(unsigned int) == sizeof(GLuint));

	GLCALL(glGenBuffers(1, &m_RenderId));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId));
}

glclass::IndexBuffer::~IndexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_RenderId));
}

void glclass::IndexBuffer::SetData(const unsigned int* data, size_t count) {
	Bind();
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

void glclass::IndexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId));
}

void glclass::IndexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
