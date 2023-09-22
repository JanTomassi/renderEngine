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
  const int type;

public:
  enum class buffer_types : uint32_t
  {
    attributes = GL_ARRAY_BUFFER,
    indices = GL_ELEMENT_ARRAY_BUFFER
  };

  /**
   * @brif Init a new buffer assiume
   * @param buffer_type set the type of the buffer
   */
  Buffer (buffer_types buffer_type);

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
