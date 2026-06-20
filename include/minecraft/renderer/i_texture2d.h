#pragma once

#include <cstdint>
#include <string>

namespace Minecraft {
  /**
   * @brief Abstract interface for a 2D texture.
   */
  class ITexture2D {
  public:
    virtual ~ITexture2D() = default;

    /**
     * @brief Binds this texture to the given texture unit.
     * @param slot Texture unit index.
     */
    virtual void bind(uint32_t slot) const = 0;

    /**
     * @brief Unbinds any texture from the given texture unit.
     * @param slot Texture unit index.
     */
    virtual void unbind(uint32_t slot) const = 0;

    /** @brief Returns the texture width in pixels. */
    [[nodiscard]] virtual uint32_t width() const = 0;

    /** @brief Returns the texture height in pixels. */
    [[nodiscard]] virtual uint32_t height() const = 0;
  };
} // namespace Minecraft
