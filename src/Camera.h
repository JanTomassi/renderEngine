#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "InputManager.h"

class Camera : public Input
{
private:
  glm::vec3 cameraPos = glm::vec3 (0.0f, 0.0f, -2.0f);
  glm::mat4 cameraRot = glm::mat4 (1.0);
  glm::vec3 cameraFront = glm::vec3 (0.0f, 0.0f, 1.0f);
  glm::vec3 cameraUp = glm::vec3 (0.0f, 1.0f, 0.0f);

  bool firstMouse = true;
  bool mouse_state = false;
  bool firstMouseKey = true;
  float lastX = 0, lastY = 0;
  float yaw = -90, pitch = 0;
  double LastTime;
  float rota = 0;

public:
  Camera ();
  ~Camera () = default;

  // Inherited via Input
  void keyfun (GLFWwindow *window, int key, int scancode, int action,
               int mods) override;

  void
  reCalculateView ()
  {
    // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), cameraFront, cameraUp);
  }

  glm::vec3
  pos ()
  {
    return cameraPos;
  }

  glm::mat4
  rot ()
  {
    return cameraRot;
  }
  glm::vec3
  front ()
  {
    return cameraFront;
  }

  // Inherited via Input
  virtual void mousefun (GLFWwindow *window, int xpos, int ypos) override;
};
