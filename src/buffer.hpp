#pragma once
namespace JRE
{
namespace glObject
{

class Buffer
{
private:
  unsigned int m_RenderId;

public:
  Buffer ();
  void set_data (int type, const void *data, unsigned int size) const;
  ~Buffer ();

  void bind () const;
  void unbind () const;
};
}
}
