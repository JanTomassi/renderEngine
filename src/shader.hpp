#pragma once
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/matrix.hpp>

namespace JRE
{
namespace glObject
{
class Shader
{
private:
  const uint32_t m_shader_program_id;
  std::vector<uint32_t> m_compiled_shader_id;
  bool is_shader_compiled = false;

  uint32_t compile_shader (uint32_t type, std::string &source,
                           const std::string &shader_name);

  /**
   * @brief Link compiled shader to program
   */
  void link_to_shader ();

public:
  /**
   * @brief Create GPU program
   */
  Shader ();

  /**
   * @brief Delete shader and GPU program
   */
  ~Shader ();

  /**
   * @brief Add compiled version of the src file to the program queue
   * @param type indicates what type of shade this is
   * @param src path to source file on disk
   */
  void add_src (uint32_t type, const std::string &src);

  /**
   * @brief Compile if there are shader to compile and then start the program
   */
  void use_program ();

  /**
   * @brief Get shader uniform location from name
   */
  uint32_t get_uniform_location (const std::string &name);

  /**
   * @brief Set shader uniform of type float with 4 elements
   */
  void set_uniform_4f (const std::string &name, float a, float b, float c,
                       float d);

  /**
   * @brief Set shader uniform of type float with a 4x4 matrix
   */
  void set_uniform_mat_4f (const std::string &name, const glm::mat4 &value);
};
}
}
