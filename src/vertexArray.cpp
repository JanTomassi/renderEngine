#include "vertexArray.hpp"
#include "buffer.hpp"
#include "bufferLayout.hpp"
#include <GL/glew.h>
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <memory>

using namespace JRE::glObject;

VertexArray::VertexArray (Buffer &&vb, helper::BufferLayout &&layout)
    : m_RenderId (), vb (std::make_shared<Buffer> (std::move (vb))),
      layout (std::make_shared<helper::BufferLayout> (std::move (layout)))
{
  glGenVertexArrays (1, const_cast<GLuint *> (&m_RenderId));

  update_vbuffer (*this->vb, *this->layout);
}

VertexArray::~VertexArray ()
{
  if (m_RenderId != UINT32_MAX)
    glDeleteVertexArrays (1, &m_RenderId);
}

VertexArray::VertexArray (VertexArray &&o)
    : m_RenderId (o.m_RenderId), vb (o.vb), layout (o.layout)
{
  o.m_RenderId = UINT32_MAX;
}
VertexArray &
VertexArray::operator= (VertexArray &&o)
{
  m_RenderId = o.m_RenderId;
  vb = o.vb;
  layout = o.layout;
  
  o.m_RenderId = UINT32_MAX;
  return *this;
}

void
VertexArray::change_vbuffer (Buffer &&vb, helper::BufferLayout &&layout)
{
  this->vb = std::make_shared<Buffer> (std::move (vb));
  this->layout = std::make_shared<helper::BufferLayout> (std::move (layout));
}

void
VertexArray::update_vbuffer (Buffer &vb, helper::BufferLayout &layout)
{
  vb.bind ();
  this->bind ();

  auto layers = layout.get_elements ();
  for (auto it = layers.cbegin (); it != layers.cend (); it++)
    {
      uint32_t index
          = static_cast<uint32_t> (std::distance (layers.cbegin (), it));
      glEnableVertexAttribArray (index);
      glVertexAttribPointer (index, static_cast<int> (it->data_count),
                             it->data_type, it->normalize,
                             static_cast<int> (layout.get_stride ()),
                             reinterpret_cast<void *> (it->data_offset));
    }

  this->unbind ();
  vb.unbind ();
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
