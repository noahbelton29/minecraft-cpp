#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <string>

#include "minecraft/renderer/i_texture2d.h"

namespace Minecraft {
  /**
   * @brief OpenGL implementation of ITexture2D.
   *
   * Loads a PNG/JPG/BMP from disk via stb_image and uploads it to the GPU.
   */
  class OpenGLTexture2D : public ITexture2D {
  public:
    /**
     * @brief Loads a texture from a file and uploads it to the GPU.
     * @param path Path to the image file.
     */
    explicit OpenGLTexture2D(const std::string &path);

    ~OpenGLTexture2D() override;

    /**
     * @brief Binds this texture to the given texture unit.
     * @param slot Texture unit index.
     */
    void bind(uint32_t slot) const override;

    /**
     * @brief Unbinds any texture from the given texture unit.
     * @param slot Texture unit index.
     */
    void unbind(uint32_t slot) const override;

    [[nodiscard]] uint32_t width() const override;
    [[nodiscard]] uint32_t height() const override;

  private:
    GLuint   textureId_ = 0;
    uint32_t width_     = 0;
    uint32_t height_    = 0;
  };
} // namespace Minecraft
