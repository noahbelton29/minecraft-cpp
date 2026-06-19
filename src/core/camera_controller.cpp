#include "minecraft/core/camera_controller.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "minecraft/core/input.h"

Minecraft::CameraController::CameraController(
    std::shared_ptr<PerspectiveCamera> camera,
    const float                        moveSpeed,
    const float                        mouseSensitivity,
    const float                        gamepadLookSpeed) :
    camera_(std::move(camera)), moveSpeed_(moveSpeed),
    mouseSensitivity_(mouseSensitivity), gamepadLookSpeed_(gamepadLookSpeed) {
}

void Minecraft::CameraController::update(const float dt) const {
  const float yawRad = glm::radians(camera_->yaw());

  const glm::vec3 forward = {glm::cos(yawRad), 0.0f, glm::sin(yawRad)};
  const glm::vec3 right   = {-forward.z, 0.0f, forward.x};

  glm::vec3 pos   = camera_->position();
  float     yaw   = camera_->yaw();
  float     pitch = camera_->pitch();

  // keyboard movement
  if (Input::isKeyDown(GLFW_KEY_W))
    pos += forward * moveSpeed_ * dt;
  if (Input::isKeyDown(GLFW_KEY_S))
    pos -= forward * moveSpeed_ * dt;
  if (Input::isKeyDown(GLFW_KEY_D))
    pos += right * moveSpeed_ * dt;
  if (Input::isKeyDown(GLFW_KEY_A))
    pos -= right * moveSpeed_ * dt;

  if (Input::isKeyDown(GLFW_KEY_SPACE))
    pos.y += moveSpeed_ * dt;
  if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
    pos.y -= moveSpeed_ * dt;

  // mouse look
  const glm::vec2 mouse = Input::mouseDelta();
  yaw += mouse.x * mouseSensitivity_;
  pitch -= mouse.y * mouseSensitivity_;

  // gamepad left stick movement
  const glm::vec2 leftStick = Input::gamepadLeftStick();
  pos += forward * (-leftStick.y) * moveSpeed_ * dt;
  pos += right * leftStick.x * moveSpeed_ * dt;

  // gamepad face buttons for vertical movement
  if (Input::isGamepadButtonDown(GLFW_GAMEPAD_BUTTON_A))
    pos.y += moveSpeed_ * dt;
  if (Input::isGamepadButtonDown(GLFW_GAMEPAD_BUTTON_B))
    pos.y -= moveSpeed_ * dt;

  // gamepad right stick look
  const glm::vec2 rightStick = Input::gamepadRightStick();
  yaw += rightStick.x * gamepadLookSpeed_ * dt;
  pitch -= rightStick.y * gamepadLookSpeed_ * dt;

  camera_->setPosition(pos);
  camera_->setRotation(yaw, pitch);
}
