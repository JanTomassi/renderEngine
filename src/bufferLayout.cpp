#include "bufferLayout.hpp"
#include <cstdint>

using namespace JRE::helper;

BufferLayout::BufferLayout () = default;

template <>
void
BufferLayout::append<GLfloat> (uint32_t count)
{
  m_layers.push_back (Layer{ GL_FLOAT, count, false, m_stride });
  m_stride += count * Layer::get_size_of_type (GL_FLOAT);
}

template <>
void
BufferLayout::append<GLuint> (uint32_t count)
{
  m_layers.push_back (Layer{ GL_UNSIGNED_INT, count, false, m_stride });
  m_stride += count * Layer::get_size_of_type (GL_UNSIGNED_INT);
}

template <>
void
BufferLayout::append<GLbyte> (uint32_t count)
{
  m_layers.push_back (Layer{ GL_BYTE, count, false, m_stride });
  m_stride += count * Layer::get_size_of_type (GL_BYTE);
}
