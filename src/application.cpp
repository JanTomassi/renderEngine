#include "window.hpp"
int
main ()
{
  JRE::WindowManager main_windows = JRE::WindowManager (640, 480);
  main_windows.start ();
  return 0;
}
