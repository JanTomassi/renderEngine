#pragma once
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <GL/glew.h>

namespace JRE
{
namespace helper
{
/**
 * @brief Describe how data are layed out in buffer
 *
 * It is used to describe to the JRE::glObject::VertexArray how
 * data are grouped in the underling buffer
 */
class BufferLayout
{
private:
  /**
   * Buffer layout is sean as a series of layers or groups of value that repeat
   * without spacing
   */
  struct Layer
  {
    const uint32_t
        data_type; /*< element/s type for single data point inference*/
    const uint32_t
        data_count; /*< number of consecutive element of the same type*/
    const bool normalize;
    const size_t data_offset; /*< offset in byte from the begining of the layer
                                 e.x. for object b: a[0-7], b[8-15], c[16-23],
                                 stride == 24, offset == 8*/

    /**
     * @brief Get the type size in bytes
     * @return size in bytes
     * @throw invalid_argument on unmatched types
     */
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

  std::vector<Layer> m_layers; /*< Array of Layer */
  uint32_t m_stride
      = 0; /*< number of bytes separating each group of data, 0 is auto */

public:
  /**
   * @brief Default constructor
   */
  BufferLayout ();

  /**
   * @brief Append to layers array a new element
   */
  template <typename T> void append (uint32_t count) = delete;

  /**
   * @brief Getter for m_layers
   */
  inline const std::vector<Layer> &
  get_elements () const
  {
    return m_layers;
  }

  /**
   * @brief Getter for m_stride
   */
  inline const uint32_t &
  get_stride () const
  {
    return m_stride;
  }
};
template <> void BufferLayout::append<GLfloat> (uint32_t count);

template <> void BufferLayout::append<GLuint> (uint32_t count);

template <> void BufferLayout::append<GLbyte> (uint32_t count);
}

}
