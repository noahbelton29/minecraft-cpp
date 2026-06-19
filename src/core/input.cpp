#include "minecraft/core/input.h"

#include <cmath>

GLFWwindow      *Minecraft::Input::window_              = nullptr;
glm::vec2        Minecraft::Input::lastMousePos_        = {0.0f, 0.0f};
glm::vec2        Minecraft::Input::mouseDelta_          = {0.0f, 0.0f};
bool             Minecraft::Input::firstUpdate_         = true;
bool             Minecraft::Input::gamepadConnected_    = false;
GLFWgamepadstate Minecraft::Input::gamepadState_        = {};
int              Minecraft::Input::connectedJoystickId_ = -1;

void Minecraft::Input::init(GLFWwindow *window) {
  window_ = window;
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Find and store the first connected gamepad at init time
  for (int joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST;
       ++joystick) {
    if (glfwJoystickIsGamepad(joystick)) {
      connectedJoystickId_ = joystick;
      const char *name     = glfwGetGamepadName(joystick);

      break;
    }
  }
}

void Minecraft::Input::update() {
  // mouse delta
  double x, y;
  glfwGetCursorPos(window_, &x, &y);

  const glm::vec2 current = {static_cast<float>(x), static_cast<float>(y)};

  if (firstUpdate_) {
    lastMousePos_ = current;
    firstUpdate_  = false;
  }

  mouseDelta_   = current - lastMousePos_;
  lastMousePos_ = current;

  // Try to find a connected gamepad each frame
  gamepadConnected_ = false;

  // First check the previously connected joystick
  if (connectedJoystickId_ != -1 &&
      glfwJoystickIsGamepad(connectedJoystickId_)) {
    gamepadConnected_ =
        glfwGetGamepadState(connectedJoystickId_, &gamepadState_);
  }

  // If no gamepad found, scan all joysticks
  if (!gamepadConnected_) {
    for (int joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST;
         ++joystick) {
      if (glfwJoystickIsGamepad(joystick)) {
        gamepadConnected_ = glfwGetGamepadState(joystick, &gamepadState_);
        if (gamepadConnected_) {
          connectedJoystickId_ = joystick;
          break;
        }
      }
    }
  }
}

bool Minecraft::Input::isKeyDown(const int key) {
  return glfwGetKey(window_, key) == GLFW_PRESS;
}

glm::vec2 Minecraft::Input::mouseDelta() {
  return mouseDelta_;
}

bool Minecraft::Input::gamepadConnected() {
  return gamepadConnected_;
}

const char *Minecraft::Input::getGamepadName() {
  if (!gamepadConnected_ || connectedJoystickId_ == -1)
    return nullptr;
  return glfwGetGamepadName(connectedJoystickId_);
}

glm::vec2 Minecraft::Input::gamepadLeftStick() {
  if (!gamepadConnected_)
    return {0.0f, 0.0f};

  return {
      applyDeadZone(gamepadState_.axes[GLFW_GAMEPAD_AXIS_LEFT_X], kDeadZone),
      applyDeadZone(gamepadState_.axes[GLFW_GAMEPAD_AXIS_LEFT_Y], kDeadZone),
  };
}

glm::vec2 Minecraft::Input::gamepadRightStick() {
  if (!gamepadConnected_)
    return {0.0f, 0.0f};

  return {
      applyDeadZone(gamepadState_.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], kDeadZone),
      applyDeadZone(gamepadState_.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y], kDeadZone),
  };
}

bool Minecraft::Input::isGamepadButtonDown(const int button) {
  if (!gamepadConnected_)
    return false;

  return gamepadState_.buttons[button] == GLFW_PRESS;
}

float Minecraft::Input::applyDeadZone(const float value, const float deadZone) {
  // if the stick is inside the dead zone treat it as zero
  if (std::abs(value) < deadZone)
    return 0.0f;

  // rescale the remaining range to [0, 1]
  const float sign = value > 0.0f ? 1.0f : -1.0f;
  return sign * (std::abs(value) - deadZone) / (1.0f - deadZone);
}
