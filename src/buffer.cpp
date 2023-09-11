#include "buffer.hpp"
#include "debug.hpp"

using namespace JRE::glObject;

Buffer::Buffer ()
{
  GLCALL (glGenBuffers (1, &m_RenderId));
  GLCALL (glBindBuffer (GL_ARRAY_BUFFER, m_RenderId));
}

void
Buffer::set_data (int type, const void *data, unsigned int size) const
{
  bind ();
  GLCALL (glBufferData (type, size, data, GL_STATIC_DRAW));
}

Buffer::~Buffer () { GLCALL (glDeleteBuffers (1, &m_RenderId)); }

void
Buffer::bind () const
{
  GLCALL (glBindBuffer (GL_ARRAY_BUFFER, m_RenderId));
}

void
Buffer::unbind () const
{
  GLCALL (glBindBuffer (GL_ARRAY_BUFFER, 0));
}
