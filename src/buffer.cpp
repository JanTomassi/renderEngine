#include "buffer.hpp"
#include "debug.hpp"

using namespace JRE::glObject;

Buffer::Buffer (int buffer_type) : type (buffer_type)
{
  glGenBuffers (1, &m_RenderId);
}

void
Buffer::set_data (const void *data, unsigned int size) const
{
  bind ();
  glBufferData (type, size, data, GL_STATIC_DRAW);
}

Buffer::~Buffer () { glDeleteBuffers (1, &m_RenderId); }

void
Buffer::bind () const
{
  glBindBuffer (type, m_RenderId);
}

void
Buffer::unbind () const
{
  glBindBuffer (type, 0);
}
