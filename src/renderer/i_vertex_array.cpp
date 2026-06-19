#include "minecraft/renderer/i_vertex_array.h"

uint32_t Minecraft::shaderDataTypeSize(const ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:  return 4;
    case ShaderDataType::Float2: return 4 * 2;
    case ShaderDataType::Float3: return 4 * 3;
    case ShaderDataType::Float4: return 4 * 4;
    case ShaderDataType::Int:    return 4;
    case ShaderDataType::Int2:   return 4 * 2;
    case ShaderDataType::Int3:   return 4 * 3;
    case ShaderDataType::Int4:   return 4 * 4;
    case ShaderDataType::Bool:   return 1;
  }
  return 0;
}

uint32_t Minecraft::shaderDataTypeComponentCount(const ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:  return 1;
    case ShaderDataType::Float2: return 2;
    case ShaderDataType::Float3: return 3;
    case ShaderDataType::Float4: return 4;
    case ShaderDataType::Int:    return 1;
    case ShaderDataType::Int2:   return 2;
    case ShaderDataType::Int3:   return 3;
    case ShaderDataType::Int4:   return 4;
    case ShaderDataType::Bool:   return 1;
  }
  return 0;
}

Minecraft::BufferElement::BufferElement(const ShaderDataType t, const bool norm) :
    type(t),
    normalized(norm),
    size(shaderDataTypeSize(t)),
    offset(0) {}

Minecraft::BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) :
    elements_(elements) {
  calculateOffsetsAndStride();
}

const std::vector<Minecraft::BufferElement> &Minecraft::BufferLayout::elements() const {
  return elements_;
}

uint32_t Minecraft::BufferLayout::stride() const {
  return stride_;
}

void Minecraft::BufferLayout::calculateOffsetsAndStride() {
  uint32_t offset = 0;
  stride_ = 0;
  for (auto &e : elements_) {
    e.offset = offset;
    offset += e.size;
    stride_ += e.size;
  }
}
