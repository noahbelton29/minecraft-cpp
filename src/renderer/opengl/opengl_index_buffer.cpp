#include "minecraft/renderer/opengl/opengl_index_buffer.h"

Minecraft::OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t *indices,
                                                const uint32_t  count) :
    count_(count) {
  glGenBuffers(1, &ibo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(count * sizeof(uint32_t)),
               indices,
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Minecraft::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  if (ibo_)
    glDeleteBuffers(1, &ibo_);
}

void Minecraft::OpenGLIndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
}

void Minecraft::OpenGLIndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t Minecraft::OpenGLIndexBuffer::count() const {
  return count_;
}
