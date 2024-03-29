# Project Settings
cmake_minimum_required(VERSION 3.20)
project(jRenderEngine
  VERSION 0.0.1
  DESCRIPTION "A simple render engine in C++ that use opengl"
)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wconversion -ggdb -DDEBUG --pedantic --std=c++20 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Wconversion --pedantic --std=c++20")

# The main executable
add_executable(jRenderEngine
  src/application.cpp

  src/buffer.cpp
  src/buffer.hpp

  src/bufferLayout.cpp
  src/bufferLayout.hpp

  src/debug.cpp
  src/debug.hpp

  src/mesh.hpp
  src/mesh.cpp

  src/mesh_parser.hpp

  src/mesh_parser/obj_parser.cpp
  src/mesh_parser/obj_parser.hpp

  src/scene.cpp
  src/scene.hpp

  src/shader.cpp
  src/shader.hpp

  src/vertexArray.cpp
  src/vertexArray.hpp
  
  src/window.cpp
  src/window.hpp
)

# Compile options
set_property(TARGET jRenderEngine PROPERTY CXX_STANDARD 20)
target_compile_options(jRenderEngine PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

target_link_libraries(jRenderEngine 
  PRIVATE glfw 
  PRIVATE libglew_static 
  PRIVATE glm)


