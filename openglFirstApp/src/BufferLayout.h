#pragma once
#include <vector>
#include <GL/glew.h>

struct BufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalize;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:	return sizeof(GLuint);
		case GL_BYTE:			return sizeof(GLbyte);
		}
	}
};

class BufferLayout
{
private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_stride;
public:
	BufferLayout();

	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count) {
		m_Elements.push_back(BufferElement{ GL_FLOAT, (unsigned int)count, false });
		m_stride += count * BufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(int count) {
		m_Elements.push_back(BufferElement{ GL_UNSIGNED_INT, (unsigned int)count, false });
		m_stride += count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(int count) {
		m_Elements.push_back(BufferElement{ GL_BYTE, (unsigned int)count, true });
		m_stride += count * BufferElement::GetSizeOfType(GL_BYTE);
	}

	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	inline const unsigned int& GetStride() const { return m_stride; }
};

