#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <vector>

#include "i_index_buffer.h"
#include "i_vertex_buffer.h"

namespace Minecraft {
  /**
   * @brief Primitive types a vertex attribute can carry.
   */
  enum class ShaderDataType : uint8_t {
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool,
  };

  /**
   * @brief Returns the byte size of a ShaderDataType.
   * @param type The type to query.
   */
  uint32_t shaderDataTypeSize(ShaderDataType type);

  /**
   * @brief Returns the number of scalar components in a ShaderDataType.
   * @param type The type to query.
   */
  uint32_t shaderDataTypeComponentCount(ShaderDataType type);

  /**
   * @brief Describes one attribute slot within a vertex layout.
   */
  struct BufferElement {
    ShaderDataType type;
    bool           normalized;
    uint32_t       size; // byte size of this element
    uint32_t       offset; // byte offset within the stride, set by BufferLayout

    /**
     * @brief Constructs a buffer element from a type and optional normalization
     * flag.
     * @param t The data type for this attribute.
     * @param norm Whether integer types should be normalized to [0, 1].
     */
    BufferElement(ShaderDataType t, bool norm = false);
  };

  /**
   * @brief Describes the memory layout of a single vertex across all its
   * attributes.
   */
  class BufferLayout {
  public:
    BufferLayout() = default;

    /**
     * @brief Constructs a layout from a list of elements and computes offsets
     * and stride.
     * @param elements Ordered list of attribute elements in this vertex.
     */
    BufferLayout(std::initializer_list<BufferElement> elements);

    /**
     * @brief Returns the list of attribute elements.
     */
    [[nodiscard]] const std::vector<BufferElement> &elements() const;

    /**
     * @brief Returns the total byte stride between consecutive vertices.
     */
    [[nodiscard]] uint32_t stride() const;

  private:
    void calculateOffsetsAndStride(); // fills offset on each element and totals
                                      // stride_

    std::vector<BufferElement> elements_;
    uint32_t                   stride_ = 0;
  };

  /**
   * @brief Abstract interface for a vertex array object.
   *
   * Owns one or more vertex buffers and an optional index buffer,
   * and records how their attributes are laid out for the GPU.
   */
  class IVertexArray {
  public:
    virtual ~IVertexArray() = default;

    /**
     * @brief Binds this vertex array for drawing.
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbinds the active vertex array.
     */
    virtual void unbind() const = 0;

    /**
     * @brief Attaches a vertex buffer and describes its layout to the GPU.
     * @param vb The vertex buffer to attach.
     * @param layout The attribute layout of the data in vb.
     */
    virtual void addVertexBuffer(std::shared_ptr<IVertexBuffer> vb,
                                 const BufferLayout            &layout) = 0;

    /**
     * @brief Attaches an index buffer to this vertex array.
     * @param ib The index buffer to attach.
     */
    virtual void setIndexBuffer(std::shared_ptr<IIndexBuffer> ib) = 0;

    /**
     * @brief Returns the currently attached index buffer, or nullptr if none.
     */
    [[nodiscard]] virtual const std::shared_ptr<IIndexBuffer> &
    indexBuffer() const = 0;
  };

} // namespace Minecraft
