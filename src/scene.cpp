#include <iostream>
#include "scene.hpp"
#include "mesh.hpp"
#include <bits/utility.h>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <utility>

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
  std::jthread ioThread ([this, file_path] () {
    auto [vex, layout, info] = Mesh::load_mesh (file_path);
    auto cb
        = [this, vex = std::move (vex), layout, info = std::move (info)] () {
            using namespace glObject;

            Buffer data_buf (Buffer::buffer_types::attributes,
                             Buffer::buffer_usage::static_draw);
            data_buf.set_data (vex.data (), sizeof (vex[0]), vex.size ());

            VertexArray va (std::move (data_buf), std::move (layout));

            std::unique_lock<std::shared_mutex> lck (meshes_mtx);
            meshes.push_back (std::tuple (std::move (va), std::move (info)));
          };

    std::unique_lock<std::shared_mutex> lck (loader_mtx);
    loaders.push_back (cb);
  });

  ioThread.detach ();
}

void
Scene::render ()
{
  {
    std::shared_lock<std::shared_mutex> lck (loader_mtx);
    for (const auto &loader : loaders)
      loader ();
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
