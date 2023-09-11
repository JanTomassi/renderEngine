#include "Input.h"
#include "InputManager.h"

Input::Input (Input *in)
{
  InputManager &inputManager = InputManager::getInstance ();
  inputManager.add (in);
}
