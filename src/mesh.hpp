#pragma once
#include <compare>
#include <cstdint>

namespace JRE
{
namespace Mesh
{
/**
 * @brief Description of a single vertex with his attributs
 */
struct Vertex
{
  float pos[3];
  float nom[3];
  float tex[2];

  auto operator<=> (const Vertex &v) const = default;
};
/**
 * @brief Index in a vertex buffer
 */
struct Index
{
  uint32_t index;
};
}
}
