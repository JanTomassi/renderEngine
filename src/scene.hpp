#pragma once
#include "mesh.hpp"
#include "vertexArray.hpp"
#include <shared_mutex>
#include <vector>

namespace JRE
{
class Scene
{
private:
  mutable std::shared_mutex meshes_mtx;
  std::vector<std::tuple<JRE::glObject::VertexArray, JRE::Mesh::Info> > meshes;

public:
  void load_mesh_sync (std::string file_path);
  void load_mesh_async (std::string file_path);
  void render ();
};
}
