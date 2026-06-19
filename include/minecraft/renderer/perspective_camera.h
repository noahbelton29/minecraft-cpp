#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "i_camera.h"

namespace Minecraft {
  /**
   * @brief A basic perspective camera with yaw/pitch rotation.
   */
  class PerspectiveCamera : public ICamera {
  public:
    /**
     * @brief Constructs a perspective camera.
     * @param fovDeg Vertical field of view in degrees.
     * @param aspect Viewport aspect ratio.
     * @param nearClip Near clipping plane distance.
     * @param farClip Far clipping plane distance.
     */
    PerspectiveCamera(float fovDeg,
                      float aspect,
                      float nearClip,
                      float farClip);

    /**
     * @brief Sets the camera position in world space.
     * @param position New world-space position.
     */
    void setPosition(const glm::vec3 &position);

    /**
     * @brief Sets the yaw and pitch of the camera.
     * @param yaw Horizontal rotation in degrees.
     * @param pitch Vertical rotation in degrees.
     */
    void setRotation(float yaw, float pitch);

    /**
     * @brief Updates the aspect ratio.
     * @param aspect New aspect ratio.
     */
    void setAspect(float aspect);

    [[nodiscard]] const glm::mat4 &viewMatrix() const override;
    [[nodiscard]] const glm::mat4 &projectionMatrix() const override;
    [[nodiscard]] const glm::mat4 &viewProjectionMatrix() const override;

    [[nodiscard]] const glm::vec3 &position() const;
    [[nodiscard]] float            yaw() const;
    [[nodiscard]] float            pitch() const;

  private:
    void recalculate(); // recomputes view, projection, and their product

    glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
    float     yaw_      = -90.0f;
    float     pitch_    = 0.0f;

    float fovDeg_   = 70.0f;
    float aspect_   = 1.0f;
    float nearClip_ = 0.1f;
    float farClip_  = 1000.0f;

    glm::mat4 view_           = glm::mat4(1.0f);
    glm::mat4 projection_     = glm::mat4(1.0f);
    glm::mat4 viewProjection_ = glm::mat4(1.0f);
  };
} // namespace Minecraft
