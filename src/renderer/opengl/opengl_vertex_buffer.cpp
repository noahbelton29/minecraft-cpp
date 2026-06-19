#include "minecraft/renderer/opengl/opengl_vertex_buffer.h"

Minecraft::OpenGLVertexBuffer::OpenGLVertexBuffer(const void       *data,
                                                  const std::size_t sizeBytes) :
    size_(sizeBytes) {
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(sizeBytes),
               data,
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Minecraft::OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
}

void Minecraft::OpenGLVertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}

void Minecraft::OpenGLVertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::size_t Minecraft::OpenGLVertexBuffer::size() const {
  return size_;
}
