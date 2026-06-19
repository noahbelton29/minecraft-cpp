#pragma once

#include <glm/mat4x4.hpp>

namespace Minecraft {
  /**
   * @brief Abstract interface for all camera types.
   */
  class ICamera {
  public:
    virtual ~ICamera() = default;

    /**
     * @brief Returns the view matrix for this camera.
     */
    [[nodiscard]] virtual const glm::mat4 &viewMatrix() const = 0;

    /**
     * @brief Returns the projection matrix for this camera.
     */
    [[nodiscard]] virtual const glm::mat4 &projectionMatrix() const = 0;

    /**
     * @brief Returns the combined view-projection matrix.
     */
    [[nodiscard]] virtual const glm::mat4 &viewProjectionMatrix() const = 0;
  };
} // namespace Minecraft
