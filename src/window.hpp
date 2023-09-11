#pragma once
#include "GLFW/glfw3.h"
#include <cstddef>
#include <cstdint>
#include <string>

namespace JRE
{
class WindowManager
{
private:
  typedef struct   {
    uint32_t width;
    uint32_t height;
    std::string window_name;
    GLFWwindow* app;
  } window_t;
  window_t main_window;

public:
  WindowManager(uint32_t x, uint32_t y);
  uint32_t start();
};
}
