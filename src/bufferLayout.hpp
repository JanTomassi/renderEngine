#pragma once
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <GL/glew.h>

namespace JRE
{
namespace helper
{
class BufferLayout
{
private:
  struct Layer
  {
    const uint32_t data_type;
    const uint32_t data_count;
    const bool normalize;

    static uint32_t
    get_size_of_type (uint32_t type)
    {
      switch (type)
        {
        case GL_FLOAT:
          return sizeof (GLfloat);
        case GL_UNSIGNED_INT:
          return sizeof (GLuint);
        case GL_BYTE:
          return sizeof (GLbyte);
        default:
          throw std::invalid_argument ("Type not implemented");
        }
    }
  };

  std::vector<Layer> m_layers;
  uint32_t m_stride = 0;

public:
  BufferLayout ();

  template <typename T> void append (uint32_t count) = delete;

  inline const std::vector<Layer> &
  get_elements () const
  {
    return m_layers;
  }
  inline const uint32_t &
  get_stride () const
  {
    return m_stride;
  }
};
}
}
