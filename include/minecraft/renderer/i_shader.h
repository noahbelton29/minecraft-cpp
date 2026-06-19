#pragma once

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
     * @brief Sets a float value on the shader.
     * @param name Name of the uniform in the shader code.
     * @param value Value to give it.
     */
    virtual void setUniform(const std::string &, float) = 0;
    /**
     * @brief Gets the backend's native handle for this shader.
     * @return The native shader ID (e.g. the OpenGL program ID).
     */
    [[nodiscard]] virtual unsigned int getNativeHandle() const = 0;
  };
} // namespace Minecraft
