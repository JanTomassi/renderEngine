#include "Camera.h"
#include <iostream>
#include "Global.h"

Camera::Camera () : Input (this){};

void
Camera::keyfun (GLFWwindow *window, int key, int scancode, int action,
                int mods)
{
  const float cameraSpeed = 5.0f;
  if (action == GLFW_REPEAT || action == GLFW_PRESS)
    {
      // std::cout << (glfwGetTime()) << '\t' << LastTimeGlobal << '\t' <<
      // (glfwGetTime() - LastTimeGlobal) << std::endl;
      const double delta_time = (glfwGetTime () - LastTimeGlobal);
      switch (key)
        {
        case (GLFW_KEY_W):
          cameraPos += (float)(cameraSpeed * delta_time) * -cameraFront;
          reCalculateView ();
          break;
        case (GLFW_KEY_S):
          cameraPos -= (float)(cameraSpeed * delta_time) * -cameraFront;
          reCalculateView ();
          break;
        case (GLFW_KEY_D):
          cameraPos -= glm::normalize (glm::cross (cameraFront, cameraUp))
                       * (float)(cameraSpeed * delta_time);
          reCalculateView ();
          break;
        case (GLFW_KEY_A):
          cameraPos += glm::normalize (glm::cross (cameraFront, cameraUp))
                       * (float)(cameraSpeed * delta_time);
          reCalculateView ();
          break;
        case (GLFW_KEY_ESCAPE):
          if (action == GLFW_PRESS)
            {
              mouse_state
                  ? glfwSetInputMode (window, GLFW_CURSOR,
                                      GLFW_CURSOR_DISABLED)
                  : glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
              mouse_state = !mouse_state;
            }
          break;
        default:
          break;
        }
    }
}

void
Camera::mousefun (GLFWwindow *window, int xpos, int ypos)
{
  if (mouse_state)
    return;
  if (firstMouse)
    {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos (glm::radians (yaw)) * cos (glm::radians (pitch));
  direction.y = sin (glm::radians (pitch));
  direction.z = sin (glm::radians (yaw)) * cos (glm::radians (pitch));
  cameraFront = glm::normalize (direction);

  // std::cout
  //	<< "Yaw: " << yaw
  //	<< " Pitch: " << pitch
  //	<< "\nX: " << direction.x
  //	<< "\tY: " << direction.y
  //	<< "\tZ: " << direction.z << std::endl;

  cameraRot
      = glm::lookAt (glm::vec3 (0.0), -direction, glm::vec3 (0.0, 1.0, 0.0));
  cameraRot = glm::inverse (cameraRot);

  // std::cout
  //	<< "\nX: " << cameraRot[0][0]
  //	<< "\tY: " << cameraRot[1][1]
  //	<< "\tZ: " << cameraRot[2][2] << std::endl;
  // cameraFront = cameraRot * glm::vec4(0.0, 0.0, 1.0, 1.0);
  reCalculateView ();
}
