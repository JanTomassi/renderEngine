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
  Buffer (int buffer_type);
  void set_data (const void *data, unsigned int size) const;
  ~Buffer ();

  void bind () const;
  void unbind () const;
};
}
}
