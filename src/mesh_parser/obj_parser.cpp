#include "obj_parser.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <sstream>

using namespace JRE::Mesh::Loader;
using namespace JRE::Mesh;

enum class StringValue : uint8_t
{
  ERROR,
  pos_vertices,
  nom_vertices,
  tex_vertices,
  face_element,

  line_element,
  par_space_vertices,
};

std::map<std::string, StringValue> s_vertex_parse;

inline void
init_map ()
{
  s_vertex_parse["v"] = StringValue::pos_vertices;
  s_vertex_parse["vn"] = StringValue::nom_vertices;
  s_vertex_parse["vt"] = StringValue::tex_vertices;
  s_vertex_parse["vp"] = StringValue::par_space_vertices;
  s_vertex_parse["f"] = StringValue::face_element;
  s_vertex_parse["l"] = StringValue::line_element;
}

inline std::array<float, 3>
ObjParser::parse_vertex_data_3 (std::istream &is)
{
  std::array<float, 3> res{ 0, 0, 0 };
  std::string line;
  std::getline (is, line);

  std::stringstream pos_stream (line);
  std::string pos_elem;
  uint8_t index = 0;
  while (!pos_stream.eof () && index < 3)
    {
      pos_stream >> pos_elem;
      float pos = std::stof (pos_elem);
      res[index++] = pos;
    }
  return res;
}

inline std::array<float, 2>
ObjParser::parse_vertex_data_2 (std::istream &is)
{
  std::array<float, 2> res{ 0, 0 };
  std::string line;
  std::getline (is, line);

  std::stringstream pos_stream (line);
  std::string pos_elem;
  uint8_t index = 0;

  while (!pos_stream.eof () && index < 2)
    {
      pos_stream >> pos_elem;
      float pos = std::stof (pos_elem);
      res[index++] = pos;
    }
  return res;
}

inline std::array<std::array<uint32_t, 3>, 3>
ObjParser::parse_face_data (std::istream &is)
{
  std::array<std::array<uint32_t, 3>, 3> res;
  std::string line;
  std::getline (is, line);

  std::stringstream pos_stream (line);
  std::string pos_elems;
  uint8_t vindex = 0;
  do
    {
      pos_stream >> pos_elems;
      size_t marker_pos[3];

      marker_pos[0] = pos_elems.find ('/');
      marker_pos[1] = pos_elems.find ('/', marker_pos[0] + 1);
      marker_pos[2] = pos_elems.length ();

      for (size_t index = 0, prev = 0; index < 3; index++)
        {
          try
            {
              auto temp = std::stoul (
                  pos_elems.substr (prev, marker_pos[index] - prev));
              res[vindex][index] = static_cast<uint32_t> (temp);
            }
          catch (std::invalid_argument &e)
            {
              res[vindex][index] = 0;
            }
          prev = marker_pos[index] + 1;
        }
    }
  while (!pos_stream.eof () && vindex++ < 3);
  return res;
}

void
ObjParser::line_parser (std::string &s, ObjParser::parser_res &res)
{
  std::stringstream ss (s);
  std::string word;
  ss >> word;

  switch (s_vertex_parse[word])
    {
    case StringValue::pos_vertices:
      {
        auto vertex_data = parse_vertex_data_3 (ss);
        res.vertex_tracker.pos += 1;
        res.pos_vertices.push_back (vertex_data);
        break;
      }
    case StringValue::nom_vertices:
      {
        auto vertex_data = parse_vertex_data_3 (ss);
        res.vertex_tracker.normal += 1;
        res.nom_vertices.push_back (vertex_data);
        break;
      }
    case StringValue::tex_vertices:
      {
        auto vertex_data = parse_vertex_data_2 (ss);
        res.vertex_tracker.texture += 1;
        res.tex_vertices.push_back (vertex_data);
        break;
      }
    case StringValue::face_element:
      {
        auto face_data = parse_face_data (ss);
        res.vertex_tracker.index += 1;
        res.face_elements.push_back (face_data);
        break;
      }
    default:
      break;
    };
}

ObjParser::parser_res
ObjParser::parse_file (std::ifstream &&in)
{
  parser_res res;
  while (!in.eof ())
    {
      std::string line;
      std::getline (in, line, '\n');
      if (line == "" || line == "\n")
        continue;

      line_parser (line, res);
    }
  return res;
}

void
ObjParser::transform_to_buffer (const parser_res &input,
                                std::vector<JRE::Mesh::Vertex> &res_vertexs,
                                std::vector<JRE::Mesh::Index> &res_indexs)
{
  for (const auto &vertexs : input.face_elements)
    for (const auto &vertex : vertexs)
      {
        JRE::Mesh::Vertex to_push;
        if (vertex[0] > 0)
          to_push.pos = input.pos_vertices[vertex[0] - 1];
        else
          to_push.pos.fill (0);
        if (vertex[1] > 0)
          to_push.tex = input.tex_vertices[vertex[1] - 1];
        else
          to_push.tex.fill (0);
        if (vertex[2] > 0)
          to_push.nom = input.nom_vertices[vertex[2] - 1];
        else
          to_push.nom.fill (0);
        if (!std::binary_search (res_vertexs.cbegin (), res_vertexs.cend (),
                                 to_push))
          {
            auto it = std::lower_bound (res_vertexs.cbegin (),
                                        res_vertexs.cend (), to_push);
            res_vertexs.insert (it, std::move (to_push));
          }
      }

  for (const auto &vertexs : input.face_elements)
    for (const auto &vertex : vertexs)
      {
        JRE::Mesh::Vertex to_find;

        if (vertex[0] > 0)
          to_find.pos = input.pos_vertices[vertex[0] - 1];
        else
          to_find.pos.fill (0);
        if (vertex[1] > 0)
          to_find.tex = input.tex_vertices[vertex[1] - 1];
        else
          to_find.tex.fill (0);
        if (vertex[2] > 0)
          to_find.nom = input.nom_vertices[vertex[2] - 1];
        else
          to_find.nom.fill (0);

        auto indx = std::lower_bound (res_vertexs.cbegin (),
                                      res_vertexs.cend (), to_find);
        if (indx != res_vertexs.cend () && *indx == to_find)
          res_indexs.push_back (JRE::Mesh::Index{ static_cast<uint32_t> (
              std::distance (res_vertexs.cbegin (), indx)) });
        else
          assert (false);
      }
}

[[nodiscard]] ObjParser::res_t
ObjParser::get_vertex_and_index (const std::string &file_path)
{
  std::vector<JRE::Mesh::Vertex> res_vertexs;
  std::vector<JRE::Mesh::Index> res_indexs;

  std::ifstream in (file_path);
  if (!in.is_open ())
    {
      throw std::invalid_argument ("Couldn't open file: " + file_path);
    }

  init_map ();

#if 0
  auto start = std::chrono::high_resolution_clock::now ();
#endif
  parser_res p_res = parse_file (std::move (in));
#if 0
  auto end = std::chrono::high_resolution_clock::now ();

  std::cout << "Time parsing: "
            << std::chrono::duration_cast<std::chrono::microseconds> (end
                                                                      - start)
            << std::endl;

  start = std::chrono::high_resolution_clock::now ();
#endif
  transform_to_buffer (std::move (p_res), res_vertexs, res_indexs);
#if 0
  end = std::chrono::high_resolution_clock::now ();

  std::cout << "Time transform: "
            << std::chrono::duration_cast<std::chrono::microseconds> (end
                                                                      - start)
            << std::endl;

  std::cout << "Size of vertex array: " << res_vertexs.size () << std::endl;
  std::cout << "Size of index array: " << res_indexs.size () << std::endl;
  std::cout << "Result of parsing: " << p_res.vertex_tracker.pos << " pos, "
            << p_res.vertex_tracker.normal << " nom, "
            << p_res.vertex_tracker.texture << " tex, "
            << p_res.vertex_tracker.index << " indx" << std::endl;
#endif

  JRE::helper::BufferLayout layout;
  layout.append<GLfloat> (3);
  layout.append<GLfloat> (3);
  layout.append<GLfloat> (2);

  return std::tuple (res_vertexs, layout,
                     JRE::Mesh::Info{ .idx = res_indexs });
}
