#pragma once

#include <memory>
#include "i_renderer.h"
#include "renderer_api.h"

namespace Minecraft {
  /**
   * @brief Factory class for creating renderer instances.
   *
   * Creates the renderer implementation based on the
   * requested RendererAPI.
   */
  class RendererFactory {
  public:
    /**
     * @brief Creates a renderer for the specified API.
     * @param api The renderer API to create.
     * @return A unique pointer to the created renderer, or nullptr if the API
     * is not supported.
     */
    static std::unique_ptr<IRenderer> create(RendererAPI api);
  };
} // namespace Minecraft
