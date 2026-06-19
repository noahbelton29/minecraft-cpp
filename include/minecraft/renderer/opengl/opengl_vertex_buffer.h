#pragma once

#include <glad/glad.h>
#include <cstddef>

#include "minecraft/renderer/i_vertex_buffer.h"

namespace Minecraft {
  /**
   * @brief OpenGL implementation of IVertexBuffer.
   */
  class OpenGLVertexBuffer : public IVertexBuffer {
  public:
    /**
     * @brief Uploads vertex data to the GPU as a static array buffer.
     * @param data Pointer to the vertex data.
     * @param sizeBytes Total size of the data in bytes.
     */
    OpenGLVertexBuffer(const void *data, std::size_t sizeBytes);

    ~OpenGLVertexBuffer() override;

    /**
     * @brief Binds this buffer as the active GL_ARRAY_BUFFER.
     */
    void bind() const override;

    /**
     * @brief Unbinds the active GL_ARRAY_BUFFER.
     */
    void unbind() const override;

    /**
     * @brief Returns the size of the buffer in bytes.
     */
    [[nodiscard]] std::size_t size() const override;

  private:
    GLuint      vbo_  = 0;
    std::size_t size_ = 0;
  };
} // namespace Minecraft
