#include "minecraft/renderer/opengl/opengl_vertex_array.h"

Minecraft::OpenGLVertexArray::OpenGLVertexArray() {
  glGenVertexArrays(1, &vao_);
}

Minecraft::OpenGLVertexArray::~OpenGLVertexArray() {
  if (vao_)
    glDeleteVertexArrays(1, &vao_);
}

void Minecraft::OpenGLVertexArray::bind() const {
  glBindVertexArray(vao_);
}

void Minecraft::OpenGLVertexArray::unbind() const {
  glBindVertexArray(0);
}

void Minecraft::OpenGLVertexArray::addVertexBuffer(
    std::shared_ptr<IVertexBuffer> vb, const BufferLayout &layout) {

  glBindVertexArray(vao_);
  vb->bind();

  // walk the layout and register each attribute against the next free location
  for (const auto &element: layout.elements()) {
    glVertexAttribPointer(
        attribIndex_,
        static_cast<GLint>(shaderDataTypeComponentCount(element.type)),
        GL_FLOAT,
        element.normalized ? GL_TRUE : GL_FALSE,
        static_cast<GLsizei>(layout.stride()),
        reinterpret_cast<const void *>(static_cast<uintptr_t>(element.offset)));
    glEnableVertexAttribArray(attribIndex_);
    attribIndex_++;
  }

  vertexBuffers_.push_back(std::move(vb));
  glBindVertexArray(0);
}

void Minecraft::OpenGLVertexArray::setIndexBuffer(
    std::shared_ptr<IIndexBuffer> ib) {
  glBindVertexArray(vao_);
  ib->bind();
  indexBuffer_ = std::move(ib);
  glBindVertexArray(0);
}

const std::shared_ptr<Minecraft::IIndexBuffer> &
Minecraft::OpenGLVertexArray::indexBuffer() const {
  return indexBuffer_;
}
