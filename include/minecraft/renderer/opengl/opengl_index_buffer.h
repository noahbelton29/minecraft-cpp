#pragma once

#include <glad/glad.h>
#include <cstdint>

#include "minecraft/renderer/i_index_buffer.h"

namespace Minecraft {
  /**
   * @brief OpenGL implementation of IIndexBuffer.
   */
  class OpenGLIndexBuffer : public IIndexBuffer {
  public:
    /**
     * @brief Uploads index data to the GPU as a static element array buffer.
     * @param indices Pointer to the index data (uint32_t).
     * @param count Number of indices.
     */
    OpenGLIndexBuffer(const uint32_t *indices, uint32_t count);

    ~OpenGLIndexBuffer() override;

    /**
     * @brief Binds this buffer as the active GL_ELEMENT_ARRAY_BUFFER.
     */
    void bind() const override;

    /**
     * @brief Unbinds the active GL_ELEMENT_ARRAY_BUFFER.
     */
    void unbind() const override;

    /**
     * @brief Returns the number of indices in this buffer.
     */
    [[nodiscard]] uint32_t count() const override;

  private:
    GLuint   ibo_   = 0;
    uint32_t count_ = 0;
  };
} // namespace Minecraft
