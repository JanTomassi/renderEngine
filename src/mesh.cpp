#include "mesh.hpp"
#include <cstddef>
#include <tuple>
#include <vector>
#include "buffer.hpp"
#include "bufferLayout.hpp"
#include "mesh_parser/obj_parser.hpp"
#include "vertexArray.hpp"

std::tuple<JRE::glObject::VertexArray, JRE::Mesh::Info>
JRE::Mesh::load_mesh (const std::string &path)
{
  using namespace glObject;
  Buffer data_buf (Buffer::buffer_types::attributes,
                   Buffer::buffer_usage::static_draw);

  auto [vertexs, layout, info]
      = Loader::ObjParser ().get_vertex_and_index (path);

  data_buf.set_data (vertexs.data (), sizeof (vertexs[0]), vertexs.size ());

  VertexArray va (std::move (data_buf), std::move (layout));

  return std::tuple (std::move(va), std::move(info));
}
