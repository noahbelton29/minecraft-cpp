#include "minecraft/renderer/renderer_factory.h"
#include "minecraft/renderer/opengl/opengl_renderer.h"

std::unique_ptr<Minecraft::IRenderer>
Minecraft::RendererFactory::create(const RendererAPI api) {
  switch (api) {
    case RendererAPI::OpenGL:
      return std::make_unique<OpenGLRenderer>();
    default:
      return nullptr;
  }
}
