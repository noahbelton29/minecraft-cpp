#pragma once

#include <string>
#include "minecraft/renderer/renderer_api.h"

namespace Minecraft {
  /**
   * @brief Resolves shader file paths for a given RendererAPI.
   *
   * Each backend keeps its shaders in its own folder under
   * resources/shaders, since shader source isn't portable between
   * APIs.
   */
  class ShaderPaths {
  public:
    /**
     * @brief Gets the folder name used for a backend's shaders.
     * @param api The renderer API.
     * @return The folder name.
     */
    static std::string getBackendFolder(RendererAPI api);

    /**
     * @brief Builds the path to a vertex shader for the given backend.
     * @param api The renderer API.
     * @param name The shader's base name.
     * @return Full path to the vertex shader file.
     */
    static std::string getVertexShaderPath(RendererAPI        api,
                                           const std::string &name);

    /**
     * @brief Builds the path to a fragment shader for the given backend.
     * @param api The renderer API.
     * @param name The shader's base name.
     * @return Full path to the fragment shader file.
     */
    static std::string getFragmentShaderPath(RendererAPI        api,
                                             const std::string &name);
  };
} // namespace Minecraft
