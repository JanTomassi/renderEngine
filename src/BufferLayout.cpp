#include "BufferLayout.h"

BufferLayout::BufferLayout()
{
}

template<>
void BufferLayout::Push<float>(int count) {
  m_Elements.push_back(BufferElement{ GL_FLOAT, (unsigned int)count, false });
  m_stride += count * BufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
void BufferLayout::Push<unsigned int>(int count) {
  m_Elements.push_back(BufferElement{ GL_UNSIGNED_INT, (unsigned int)count, false });
  m_stride += count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void BufferLayout::Push<unsigned char>(int count) {
  m_Elements.push_back(BufferElement{ GL_BYTE, (unsigned int)count, true });
  m_stride += count * BufferElement::GetSizeOfType(GL_BYTE);
}
