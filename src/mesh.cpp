#include "mesh.hpp"
#include <cstddef>
#include <tuple>
#include <vector>
#include "buffer.hpp"
#include "bufferLayout.hpp"
#include "mesh_parser/obj_parser.hpp"
#include "vertexArray.hpp"

JRE::Mesh::Loader::MeshParser::res_t
JRE::Mesh::load_mesh (const std::string &path)
{
  /*< TODO: add check for supported file types*/

  Loader::MeshParser::res_t res
      = Loader::ObjParser ().get_vertex_and_index (path);

  return res;
}
