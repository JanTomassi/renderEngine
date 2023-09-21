#include "window.hpp"
int
main ()
{
  JRE::WindowManager main_windows = JRE::WindowManager (640, 480);

  return main_windows.start ();
}
