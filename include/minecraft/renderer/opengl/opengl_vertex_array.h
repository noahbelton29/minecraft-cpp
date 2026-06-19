#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>

#include "minecraft/renderer/i_vertex_array.h"

namespace Minecraft {
  /**
   * @brief OpenGL implementation of IVertexArray.
   */
  class OpenGLVertexArray : public IVertexArray {
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    /**
     * @brief Binds this VAO.
     */
    void bind() const override;

    /**
     * @brief Unbinds the active VAO.
     */
    void unbind() const override;

    /**
     * @brief Attaches a vertex buffer and sets up its attrib pointers.
     * @param vb The vertex buffer to attach.
     * @param layout The attribute layout of vb's data.
     */
    void addVertexBuffer(std::shared_ptr<IVertexBuffer> vb,
                         const BufferLayout            &layout) override;

    /**
     * @brief Attaches an index buffer to this VAO.
     * @param ib The index buffer to attach.
     */
    void setIndexBuffer(std::shared_ptr<IIndexBuffer> ib) override;

    /**
     * @brief Returns the attached index buffer, or nullptr if none.
     */
    [[nodiscard]] const std::shared_ptr<IIndexBuffer> &
    indexBuffer() const override;

  private:
    GLuint   vao_         = 0;
    uint32_t attribIndex_ = 0; // tracks the next free attribute location

    std::vector<std::shared_ptr<IVertexBuffer>>
                                  vertexBuffers_; // keeps VBOs alive
    std::shared_ptr<IIndexBuffer> indexBuffer_;
  };
} // namespace Minecraft
