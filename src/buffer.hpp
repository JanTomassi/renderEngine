#pragma once
namespace JRE
{
namespace glObject
{

class Buffer
{
private:
  unsigned int m_RenderId;
  const int type;

public:
  /**
   * @brif Init a new buffer assiume
   * @param buffer_type set the type of the buffer
   */
  Buffer (int buffer_type);

  /**
   * @brif set the opengl buffer data
   * @param type is the GL_{Type}_BUFFER
   * @param data pointer to the start of the data, data must be contiguse
   * @param size expressed in byte
   * @return if the call was successful
   */
  void set_data (const void *data, unsigned int size) const;

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
};
}
}
