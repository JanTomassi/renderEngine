#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/vec3.hpp>
#include <array>
#include <mutex>
#include "Debug.h"
#include "objLoader.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"

namespace object
{
static std::mutex mx;
class Mesh
{
private:
  objLoader *obj;
  unsigned int face_number;
  glclass::VertexArray va;
  glclass::Buffer vb;
  glclass::IndexBuffer ib;

public:
  Mesh (std::string p);
  void loadMesh ();
  void Allocate ();
  ~Mesh ();

  void render ();
  void Activate ();
  void Disactivate ();
};
}
