#pragma once

#include <cstddef>

namespace Minecraft {
  /**
   * @brief Abstract interface for a GPU vertex buffer.
   */
  class IVertexBuffer {
  public:
    virtual ~IVertexBuffer() = default;

    /**
     * @brief Binds this buffer as the active GL_ARRAY_BUFFER.
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbinds the active GL_ARRAY_BUFFER.
     */
    virtual void unbind() const = 0;

    /**
     * @brief Returns the size of the buffer in bytes.
     */
    [[nodiscard]] virtual std::size_t size() const = 0;
  };
} // namespace Minecraft
