#pragma once

#include <cstdint>

namespace Minecraft {
  /**
   * @brief Abstract interface for a GPU index buffer.
   */
  class IIndexBuffer {
  public:
    virtual ~IIndexBuffer() = default;

    /**
     * @brief Binds this buffer as the active GL_ELEMENT_ARRAY_BUFFER.
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbinds the active GL_ELEMENT_ARRAY_BUFFER.
     */
    virtual void unbind() const = 0;

    /**
     * @brief Returns the number of indices stored in this buffer.
     */
    [[nodiscard]] virtual uint32_t count() const = 0;
  };
} // namespace Minecraft
