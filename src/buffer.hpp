#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <cstdint>

namespace JRE
{
namespace glObject
{
/**
 * @brif Opengl buffer's manager
 * @description see https://www.khronos.org/opengl/wiki/Buffer_Object to get a
 * more detail description
 */
class Buffer
{
private:
  unsigned int m_RenderId;
  size_t count;
  const uint32_t type;
  const uint32_t usage;

public:
  enum class buffer_types : uint32_t
  {
    attributes = GL_ARRAY_BUFFER,
    indices = GL_ELEMENT_ARRAY_BUFFER
  };
 
  enum class buffer_usage : uint32_t
  {
    stream_draw = GL_STREAM_DRAW,
    stream_read = GL_STREAM_READ,
    stream_copy = GL_STREAM_COPY,
    static_draw = GL_STATIC_DRAW,
    static_read = GL_STATIC_READ,
    static_copy = GL_STATIC_COPY,
    dynamic_draw = GL_DYNAMIC_DRAW,
    dynamic_read = GL_DYNAMIC_READ,
    dynamic_copy = GL_DYNAMIC_COPY,
  };

  /**
   * @brif Init a new buffer assiume
   * @param buffer_type set the type of the buffer
   */
  Buffer (buffer_types buffer_type, buffer_usage usage);

  /**
   * @brif set the opengl buffer data
   * @param type is the GL_{Type}_BUFFER
   * @param data pointer to the start of the data, data must be contiguse
   * @param size expressed in byte
   * @return if the call was successful
   */
  void set_data (const void *data, uint8_t ssize, size_t count);

  /**
   * @brif delete the underling opengl buffer
   */
  ~Buffer ();

  /**
   * @brif bind the opengl buffer from the context
   */
  void bind () const;

  /**
   * @brif unbing the opengl buffer from the context
   */
  void unbind () const;

  /**
   * @brief Get the number of element inside the buffer
   */
  size_t get_count () const;
};
}
}
