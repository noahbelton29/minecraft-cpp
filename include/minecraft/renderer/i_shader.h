#pragma once

#include <glm/mat4x4.hpp>
#include <string>

namespace Minecraft {
  /**
   * @brief Interface for shader implementations.
   */
  class IShader {
  public:
    virtual ~IShader() = default;

    /**
     * @brief Activates this shader for drawing.
     */
    virtual void bind() = 0;

    /**
     * @brief Sets a float uniform on the shader.
     * @param name  Name of the uniform in the shader code.
     * @param value Value to set.
     */
    virtual void setUniform(const std::string &name, float value) = 0;

    /**
     * @brief Sets an int uniform on the shader (also used for sampler2D slots).
     * @param name  Name of the uniform in the shader code.
     * @param value Value to set.
     */
    virtual void setUniform(const std::string &name, int value) = 0;

    /**
     * @brief Sets a mat4 uniform on the shader.
     * @param name  Name of the uniform in the shader code.
     * @param value Value to set.
     */
    virtual void setUniform(const std::string &name,
                            const glm::mat4   &value) = 0;

    /**
     * @brief Gets the backend's native handle for this shader.
     * @return The native shader ID (e.g. the OpenGL program ID).
     */
    [[nodiscard]] virtual unsigned int getNativeHandle() const = 0;
  };
} // namespace Minecraft
