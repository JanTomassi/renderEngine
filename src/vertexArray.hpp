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
  GLuint m_RenderId;          /*< Set the Vertexarray index */
  std::shared_ptr<Buffer> vb; /*< opengl vertex buffer */
  std::shared_ptr<helper::BufferLayout>
      layout; /*< layout of the a single vertex in vb */

  /**
   * @brief Update the underling vertex buffer and specify the layout of the
   * data
   */
  void update_vbuffer (Buffer &vb, helper::BufferLayout &layout);

public:
  /**
   * @brief Init object in the opengl context
   */
  VertexArray (Buffer &&vb, helper::BufferLayout &&layout);
  /**
   * @brief Delete object from the opengl context
   */
  ~VertexArray ();

  VertexArray (const VertexArray &o) = delete;
  VertexArray &operator= (const VertexArray &o) = delete;

  VertexArray (VertexArray &&o);
  VertexArray &operator= (VertexArray &&o);

  /**
   * @brief Change the underling vertex buffer and specify the layout of the
   * data
   */
  void change_vbuffer (Buffer &&vb, helper::BufferLayout &&layout);

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
