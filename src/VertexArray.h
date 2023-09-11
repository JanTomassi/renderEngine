#pragma once
#include "BufferLayout.h"
#include "Buffer.h"
namespace glclass
{
class VertexArray
{
private:
  unsigned int m_RenderId;

public:
  VertexArray ();
  ~VertexArray ();

  void AddBuffer (const glclass::Buffer &vb, const BufferLayout &layout);

  void Bind () const;
  void Unbind () const;
};
}
