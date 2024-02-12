#include "buffer.hpp"
#include <cstddef>
#include <cstdint>

using namespace JRE::glObject;

Buffer::Buffer (buffer_types buffer_type, buffer_usage usage)
    : type (static_cast<uint32_t> (buffer_type)),
      usage (static_cast<uint32_t> (usage))
{
  glGenBuffers (1, &m_RenderId);
}

Buffer::Buffer (Buffer &&o)
    : m_RenderId (o.m_RenderId), type (o.type), usage (o.usage)
{
  o.m_RenderId = UINT32_MAX;
}
Buffer &
Buffer::operator= (Buffer &&o)
{
  m_RenderId = o.m_RenderId;
  type = o.type;
  usage = o.usage;

  o.m_RenderId = UINT32_MAX;
  return *this;
}

void
Buffer::set_data (const void *data, uint8_t ssize, size_t count)
{
  bind ();
  glBufferData (type, static_cast<long> (ssize * count), data, usage);
  this->count = count;
}

Buffer::~Buffer ()
{
  if (m_RenderId != UINT32_MAX)
    glDeleteBuffers (1, &m_RenderId);
}

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

size_t
Buffer::get_count () const
{
  return count;
}
