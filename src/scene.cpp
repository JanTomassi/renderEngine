#include "scene.hpp"
#include "mesh.hpp"
#include <future>
#include <mutex>
#include <shared_mutex>
#include <string>

namespace JRE
{
void
Scene::load_mesh_sync (std::string file_path)
{
  auto res = Mesh::load_mesh (file_path);
  std::unique_lock<std::shared_mutex> lck (meshes_mtx);
  meshes.push_back (std::move (res));
}

void
Scene::load_mesh_async (std::string file_path)
{
  auto res = std::async (std::launch::async, &Scene::load_mesh_sync, this,
                         file_path);
}

void
Scene::render ()
{
  std::shared_lock<std::shared_mutex> lck (meshes_mtx);
  for (auto &[va, info] : meshes)
    {
      va.bind ();
      glDrawElements (GL_TRIANGLES, static_cast<int> (info.idx.size ()),
                      GL_UNSIGNED_INT, info.idx.data ());
    }
}
}
