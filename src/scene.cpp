#include "scene.hpp"
#include "mesh.hpp"
#include <bits/utility.h>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <string>

namespace JRE
{
void
Scene::load_mesh_sync (std::string file_path)
{
  using namespace glObject;

  auto [vex, layout, info] = Mesh::load_mesh (file_path);

  Buffer data_buf (Buffer::buffer_types::attributes,
                   Buffer::buffer_usage::static_draw);
  data_buf.set_data (vex.data (), sizeof (vex[0]), vex.size ());

  VertexArray va (std::move (data_buf), std::move (layout));

  std::unique_lock<std::shared_mutex> lck (meshes_mtx);
  meshes.push_back (std::tuple (std::move (va), std::move (info)));
}

void
Scene::load_mesh_async (std::string file_path)
{
  auto res = std::async (std::launch::async, [&] () {
    auto [vex, layout, info] = Mesh::load_mesh (file_path);

    auto res = std::async (std::launch::deferred, [&] () {
      using namespace glObject;
      Buffer data_buf (Buffer::buffer_types::attributes,
                       Buffer::buffer_usage::static_draw);
      data_buf.set_data (vex.data (), sizeof (vex[0]), vex.size ());

      VertexArray va (std::move (data_buf), std::move (layout));

      std::unique_lock<std::shared_mutex> lck (meshes_mtx);
      meshes.push_back (std::tuple (std::move (va), std::move (info)));
    });
    return res;
  });
  std::unique_lock<std::shared_mutex> lck (loader_mtx);
  loaders.push_back (std::move (res));
}

void
Scene::render ()
{
  {
    std::shared_lock<std::shared_mutex> lck (loader_mtx);
    for (auto &loader : loaders)
      loader.wait ();
    loaders.clear ();
  }
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
}
