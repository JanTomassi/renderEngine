#include "buffer.hpp"
#include <cstddef>

using namespace JRE::glObject;

Buffer::Buffer (buffer_types buffer_type)
    : type (static_cast<int> (buffer_type))
{
  glGenBuffers (1, &m_RenderId);
}

void
Buffer::set_data (const void *data, uint8_t ssize, size_t count)
{
  bind ();
  glBufferData (type, static_cast<long> (ssize * count), data, usage);
  this->count = count;
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
