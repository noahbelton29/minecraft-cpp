#include "minecraft/renderer/shader_factory.h"
#include "minecraft/renderer/opengl/opengl_shader.h"

std::unique_ptr<Minecraft::IShader>
Minecraft::ShaderFactory::create(const RendererAPI  api,
                                  const std::string &vertexSource,
                                  const std::string &fragmentSource) {
  switch (api) {
    case RendererAPI::OpenGL:
      return std::make_unique<OpenGLShader>(vertexSource, fragmentSource);
    default:
      return nullptr;
  }
}
