#include "minecraft/util/shader_paths.h"

std::string Minecraft::ShaderPaths::getBackendFolder(const RendererAPI api) {
  switch (api) {
    case RendererAPI::OpenGL:
      return "opengl";
    default:
      return "unknown";
  }
}

std::string
Minecraft::ShaderPaths::getVertexShaderPath(const RendererAPI  api,
                                            const std::string &name) {
  switch (api) {
    case RendererAPI::OpenGL:
      return "resources/shaders/" + getBackendFolder(api) + "/" + name + ".vsh";
    default:
      return "";
  }
}

std::string
Minecraft::ShaderPaths::getFragmentShaderPath(const RendererAPI  api,
                                              const std::string &name) {
  switch (api) {
    case RendererAPI::OpenGL:
      return "resources/shaders/" + getBackendFolder(api) + "/" + name + ".fsh";
    default:
      return "";
  }
}
