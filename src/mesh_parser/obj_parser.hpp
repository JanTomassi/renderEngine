#include "../mesh_parser.hpp"
#include <array>
#include <cstdint>

namespace JRE
{
namespace Mesh
{
namespace Loader
{
class ObjParser : public MeshParser
{
private:
  typedef std::array<float, 3> d3array;
  typedef std::array<float, 2> d2array;
  typedef std::array<std::array<uint32_t, 3>, 3> vertex_index;
  typedef struct
  {
    uint32_t pos;
    uint32_t normal;
    uint32_t texture;
    uint32_t index;
  } n_vertex;
  typedef struct parser_res_struct
  {
    std::vector<std::array<float, 3> > pos_vertices;
    std::vector<std::array<float, 3> > nom_vertices;
    std::vector<std::array<float, 2> > tex_vertices;
    std::vector<std::array<std::array<uint32_t, 3>, 3> > face_elements;
    n_vertex vertex_tracker{ 0, 0, 0, 0 };
  } parser_res;

  inline d3array parse_vertex_data_3 (std::istream &is);
  inline d2array parse_vertex_data_2 (std::istream &is);
  inline vertex_index parse_face_data (std::istream &is);

  void line_parser (std::string &s, parser_res &res);
  parser_res parse_file (std::ifstream &&in);
  void transform_to_buffer (const parser_res &input,
                            std::vector<JRE::Mesh::Vertex> &res_vertexs,
                            std::vector<JRE::Mesh::Index> &res_indexs);

public:
  [[nodiscard]]std::tuple<std::vector<JRE::Mesh::Vertex>, std::vector<JRE::Mesh::Index> >
  get_vertex_and_index (const std::string &file_path) override;
};
}
}
}
