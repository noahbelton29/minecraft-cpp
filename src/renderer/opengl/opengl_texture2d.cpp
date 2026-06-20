#include "minecraft/renderer/opengl/opengl_texture2d.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Minecraft::OpenGLTexture2D::OpenGLTexture2D(const std::string &path) {
  stbi_set_flip_vertically_on_load(true);

  int            w, h, channels;
  unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 0);

  if (!data) {
    std::cerr << "Failed to load texture: " << path << "\n";
    return;
  }

  width_  = static_cast<uint32_t>(w);
  height_ = static_cast<uint32_t>(h);

  const GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

  glGenTextures(1, &textureId_);
  glBindTexture(GL_TEXTURE_2D, textureId_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               static_cast<GLint>(format),
               w,
               h,
               0,
               format,
               GL_UNSIGNED_BYTE,
               data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}

Minecraft::OpenGLTexture2D::~OpenGLTexture2D() {
  if (textureId_)
    glDeleteTextures(1, &textureId_);
}

void Minecraft::OpenGLTexture2D::bind(const uint32_t slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, textureId_);
}

void Minecraft::OpenGLTexture2D::unbind(const uint32_t slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Minecraft::OpenGLTexture2D::width() const {
  return width_;
}
uint32_t Minecraft::OpenGLTexture2D::height() const {
  return height_;
}
