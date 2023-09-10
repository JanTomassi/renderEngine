#pragma once
#include <vector>
#include <GL/glew.h>

struct BufferElement
{
  unsigned int type;
  unsigned int count;
  bool normalize;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
    case GL_FLOAT:        return sizeof(GLfloat);
    case GL_UNSIGNED_INT: return sizeof(GLuint);
    case GL_BYTE:         return sizeof(GLbyte);
    }
    return -1;
  }
};

class BufferLayout
{
private:
  std::vector<BufferElement> m_Elements;
  unsigned int m_stride;
public:
  BufferLayout();

  template<typename T>
  void Push(int count) {
    static_assert(true);
  }

  inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
  inline const unsigned int& GetStride() const { return m_stride; }
};

