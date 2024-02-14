#pragma once
#include "vertexArray.hpp"
#include <compare>
#include <cstddef>
#include <cstdint>
#include <string>
#include <array>
#include <vector>

namespace JRE
{
namespace Mesh
{
/**
 * @brief Description of a single vertex with his attributs
 */
struct Vertex
{
  std::array<float, 3> pos;
  std::array<float, 3> nom;
  std::array<float, 2> tex;

  auto operator<=> (const Vertex &v) const = default;
};
/**
 * @brief Index in a vertex buffer
 */
struct Index
{
  uint32_t index;
};

struct Info
{
  std::vector<Index> idx;
};

/**
 * @brief Load a mesh in memory
 * @return the VertexArray that own all the mesh data and a vector of idx of
 * triangles
 */
std::tuple<JRE::glObject::VertexArray, JRE::Mesh::Info>
load_mesh (const std::string &path);
}
}
