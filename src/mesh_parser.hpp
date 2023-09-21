#pragma once
#include <string>
#include <vector>
#include "mesh.hpp"

namespace JRE
{
namespace Mesh
{
namespace Loader
{
class MeshParser
{
private:
  typedef std::tuple<std::vector<JRE::Mesh::Vertex>,
                     std::vector<JRE::Mesh::Index> >
      vertex_index_tuple;

public:
  /**
   * @brief Get a vector representation to put inside a opengl buffer
   */
  virtual vertex_index_tuple
  get_vertex_and_index (const std::string &file_path)
      = 0;
};
}
}
}
