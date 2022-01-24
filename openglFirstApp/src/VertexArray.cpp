#include "vertexArray.h"
#include "Debug.h"

glclass::VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_RenderId));
	GLCALL(glBindVertexArray(m_RenderId));
}

glclass::VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &m_RenderId));
}

void glclass::VertexArray::AddBuffer(const glclass::Buffer& vb, const BufferLayout& layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalize, layout.GetStride(), (const void*)offset));
		offset += element.count * BufferElement::GetSizeOfType(element.type);
	}
}

void glclass::VertexArray::Bind() const
{
	GLCALL(glBindVertexArray(m_RenderId))
}

void glclass::VertexArray::Unbind() const
{
	GLCALL(glBindVertexArray(0))
}
