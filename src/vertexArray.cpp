#include "vertexArray.hpp"
#include "bufferLayout.hpp"
#include <GL/glew.h>
#include <cstddef>
#include <cstdint>
#include <algorithm>

using namespace JRE::glObject;

VertexArray::VertexArray () : m_RenderId ()
{
  glGenVertexArrays (1, const_cast<GLuint *> (&m_RenderId));
}

VertexArray::~VertexArray () { glDeleteVertexArrays (1, &m_RenderId); }

void
VertexArray::set_vbuffer (const Buffer &vb, const helper::BufferLayout layout)
{
  this->bind ();
  vb.bind ();

  auto layers = layout.get_elements ();
  for (auto it = layers.cbegin (); it != layers.cend (); it++)
    {
      size_t index = std::distance (layers.cbegin (), it);
      glEnableVertexAttribArray (index);
      glVertexAttribPointer (index, it->data_count, it->data_type,
                             it->normalize, layout.get_stride (),
                             reinterpret_cast<void *> (it->data_offset));
    }

  vb.unbind ();
  this->unbind ();
}

void
VertexArray::bind ()
{
  glBindVertexArray (m_RenderId);
}

void
VertexArray::unbind ()
{
  glBindVertexArray (0);
}
