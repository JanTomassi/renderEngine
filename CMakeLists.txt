# Project Settings
cmake_minimum_required(VERSION 3.2)
project(jRenderEngine
  VERSION 0.0.2
  DESCRIPTION "A simple render engine in C++ that use opengl"
)

# The main executable
add_executable(jRenderEngine
  src/Application.cpp
  src/Buffer.cpp
  src/Buffer.h
  src/BufferLayout.cpp
  src/BufferLayout.h
  src/Camera.cpp
  src/Camera.h
  src/Debug.h
  src/Global.cpp
  src/Global.h
  src/IndexBuffer.cpp
  src/IndexBuffer.h
  src/Input.cpp
  src/Input.h
  src/InputManager.cpp
  src/InputManager.h
  src/Mesh.cpp
  src/Mesh.h
  src/Scene.cpp
  src/Scene.h
  src/Texture.cpp
  src/Texture.h
  src/VertexArray.cpp
  src/VertexArray.h
  src/Window.cpp
  src/Window.h
  src/objLoader.cpp
  src/objLoader.h
  src/shader.cpp
  src/shader.h
)

# Compile options
# set_property(TARGET jRenderEngine PROPERTY CXX_STANDARD 11)
target_compile_options(jRenderEngine PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

target_link_libraries(jRenderEngine 
  PRIVATE glfw 
  PRIVATE libglew_static 
  PRIVATE glm)


