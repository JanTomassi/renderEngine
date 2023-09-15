#pragma once
#include <GL/glew.h>
#include <memory>
#include "buffer.hpp"
#include "bufferLayout.hpp"

namespace JRE
{
namespace glObject
{
/**
 * @brief This is a wrapper class for Opengl Vertex Array
 */
class VertexArray
{
private:
  const GLuint m_RenderId; /*< Set the Vertexarray index */

public:
  /**
   * @brief Init object in the opengl context
   */
  VertexArray ();
  /**
   * @brief Delete object from the opengl context
   */
  ~VertexArray ();

  /**
   * @brief Set the underling vertex buffer and specify the layout of the data
   */
  void set_vbuffer (const Buffer &vb, const helper::BufferLayout layout);

  /**
   * @brief Bind this Vertex Array to the context
   */
  void bind ();
  /**
   * @brief Unbind this Vertex Array to the context
   */
  void unbind ();
};
}
}
