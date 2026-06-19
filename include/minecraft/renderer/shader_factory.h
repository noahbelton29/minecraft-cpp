#pragma once

#include <memory>
#include <string>
#include "i_shader.h"
#include "renderer_api.h"

namespace Minecraft {
  /**
   * @brief Factory class for creating shader instances.
   *
   * Creates the shader implementation based on the
   * requested RendererAPI.
   */
  class ShaderFactory {
  public:
    /**
     * @brief Creates a shader for the specified API.
     * @param api The renderer API to create the shader for.
     * @param vertexSource Vertex shader source code.
     * @param fragmentSource Fragment shader source code.
     * @return A unique pointer to the created shader, or nullptr if the API
     * is not supported.
     */
    static std::unique_ptr<IShader> create(RendererAPI        api,
                                            const std::string &vertexSource,
                                            const std::string &fragmentSource);
  };
} // namespace Minecraft
