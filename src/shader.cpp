#include "shader.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

using namespace JRE::glObject;

// Private functions

uint32_t
report_compile_error (uint32_t shader_id, const std::string &shader_name)
{
  int msg_length;
  char *message;
  glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &msg_length);

  message = static_cast<char *> (
      alloca (msg_length * sizeof (char))); // Allocate on the stack

  glGetShaderInfoLog (shader_id, msg_length, &msg_length, message);

  std::cerr << "\033[31m"
            << "[Failed to compile shader] ";
  std::cerr << shader_name << ":" << message << "\033[0m" << std::endl;

  glDeleteShader (shader_id);
  return 0;
}

uint32_t
Shader::compile_shader (uint32_t type, std::string &source,
                        const std::string &shader_name)
{
  uint32_t shader_id = glCreateShader (type);
  const char *src = source.c_str ();
  glShaderSource (shader_id, 1, &src, NULL);
  glCompileShader (shader_id);

  int res;
  glGetShaderiv (shader_id, GL_COMPILE_STATUS, &res);
  if (res == GL_FALSE)
    {
      report_compile_error (shader_id, shader_name);
      return 0;
    }

  return shader_id;
}

void
report_link_error (const uint32_t program_id)
{
  int msg_length;
  char *message;
  glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &msg_length);
  message = static_cast<char *> (
      alloca (msg_length * sizeof (char))); // Allocate ont he stack

  glGetProgramInfoLog (program_id, 1024, &msg_length, message);
  std::cerr << "\033[31m"
            << "[Error in linking] " << std::endl;
  std::cerr << message << "\033[0m" << std::endl;
}

void
Shader::link_to_shader ()
{
  for (size_t i = 0; i < m_compiled_shader_id.size (); i++)
    glAttachShader (m_shader_program_id, m_compiled_shader_id[i]);

  glLinkProgram (m_shader_program_id);

  // Testo for linking error
  int is_program_linked;
  glGetProgramiv (m_shader_program_id, GL_LINK_STATUS, &is_program_linked);
  if (is_program_linked != GL_TRUE)
    report_link_error (m_shader_program_id);

  glValidateProgram (m_shader_program_id);

  for (size_t i = 0; i < m_compiled_shader_id.size (); i++)
    glDetachShader (m_shader_program_id, m_compiled_shader_id[i]);
}

// Public funcitons

Shader::Shader () : m_shader_program_id (glCreateProgram ()){};

Shader::~Shader ()
{
  std::for_each (m_compiled_shader_id.cbegin (), m_compiled_shader_id.cend (),
                 [] (uint32_t it) { glDeleteShader (it); });
  glDeleteProgram (m_shader_program_id);
}

void
file_to_string (std::ifstream &in, std::string &shader_string)
{
  std::string c;
  std::getline (in, c);
  if (c != "")
    shader_string += c;
  shader_string += '\n';
}

void
Shader::add_src (uint32_t type, const std::string &src)
{
  std::ifstream in (src);
  std::string shader_string;

  if (!in.is_open ())
    return; // Quit if the file can't be open or dosen't exist

  while (!in.eof ())
    file_to_string (in, shader_string);
  shader_string += '\n';

  uint32_t id = compile_shader (type, shader_string, src);
  m_compiled_shader_id.push_back (id);

  shader_string.clear ();
  in.close ();
}

void
Shader::use_program ()
{
  if (!is_shader_compiled)
    link_to_shader ();
  glUseProgram (m_shader_program_id);
}

uint32_t
Shader::get_uniform_location (const std::string &name)
{
  return glGetUniformLocation (m_shader_program_id, name.c_str ());
}

void
Shader::set_uniform_4f (const std::string &name, float a, float b, float c,
                        float d)
{
  glUniform4f (get_uniform_location (name), a, b, c, d);
}

void
Shader::set_uniform_mat_4f (const std::string &name, const glm::mat4 &value)
{
  glUniformMatrix4fv (get_uniform_location (name), 1, GL_FALSE,
                      glm::value_ptr (value));
}
