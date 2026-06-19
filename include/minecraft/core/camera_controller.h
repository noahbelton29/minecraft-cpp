#pragma once

#include <memory>

#include "minecraft/renderer/perspective_camera.h"

namespace Minecraft {
  /**
   * @brief Drives a PerspectiveCamera from keyboard, mouse, and gamepad input.
   */
  class CameraController {
  public:
    /**
     * @brief Constructs a controller for the given camera.
     * @param camera The camera to drive.
     * @param moveSpeed Units per second for movement.
     * @param mouseSensitivity Degrees per pixel for mouse look.
     * @param gamepadLookSpeed Degrees per second for right stick look.
     */
    explicit CameraController(std::shared_ptr<PerspectiveCamera> camera,
                              float moveSpeed        = 5.0f,
                              float mouseSensitivity = 0.1f,
                              float gamepadLookSpeed = 150.0f);

    /**
     * @brief Reads input and updates the camera for this frame.
     * @param dt Delta time in seconds since the last frame.
     */
    void update(float dt) const;

  private:
    std::shared_ptr<PerspectiveCamera> camera_;
    float                              moveSpeed_;
    float                              mouseSensitivity_;
    float gamepadLookSpeed_; // degrees per second at full stick deflection
  };
} // namespace Minecraft
