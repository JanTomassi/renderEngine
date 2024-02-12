#pragma once
#include "bufferLayout.hpp"
#include "vertexArray.hpp"
#include <compare>
#include <cstddef>
#include <cstdint>
#include <string>
#include <array>

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

/**
 * @brief Load a mesh in memory
 * @return A unique-id to identify the mesh or -1 for error
 */
std::tuple<JRE::glObject::VertexArray, std::vector<JRE::Mesh::Index> >
load_mesh (const std::string &path);
}
}
