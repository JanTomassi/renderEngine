#include "buffer.hpp"
#include "debug.hpp"

using namespace JRE::glObject;
/**
 * @brif Init a new buffer assiume
 * @param buffer_type set the type of the buffer
 */
Buffer::Buffer (int buffer_type): type(buffer_type)
{
  glGenBuffers (1, &m_RenderId);
}

/**
 * @brif set the opengl buffer data
 * @param type is the GL_{Type}_BUFFER
 * @param data pointer to the start of the data, data must be contiguse
 * @param size expressed in byte
 * @return if the call was successful
 */
void
Buffer::set_data (const void *data, unsigned int size) const
{
  bind ();
  glBufferData (type, size, data, GL_STATIC_DRAW);
}

/**
 * @brif delete the underling opengl buffer
 */
Buffer::~Buffer () { glDeleteBuffers (1, &m_RenderId); }

/**
 * @brif bind the opengl buffer from the context
 */
void
Buffer::bind () const
{
  glBindBuffer (type, m_RenderId);
}

/**
 * @brif unbing the opengl buffer from the context
 */
void
Buffer::unbind () const
{
  glBindBuffer (type, 0);
}
