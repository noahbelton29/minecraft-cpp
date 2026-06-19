#include "minecraft/renderer/opengl/opengl_renderer.h"
#include <iostream>

bool Minecraft::OpenGLRenderer::init() {
  std::cout << "Initializing OpenGL Renderer\n";

  if (!gladLoadGL()) {
    std::cerr << "Failed to load OpenGL functions\n";
    return false;
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";

  glViewport(0, 0, 800, 600);

  glEnable(GL_DEPTH_TEST);
  return true;
}

void Minecraft::OpenGLRenderer::shutdown() {
}

void Minecraft::OpenGLRenderer::render() {
  setClearColor(0.1f, 0.9f, 1.0f, 1.0f);
  clear();
}

void Minecraft::OpenGLRenderer::clear() {
  glClearColor(clearColor_[0], clearColor_[1], clearColor_[2], clearColor_[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Minecraft::OpenGLRenderer::setClearColor(const float red,
                                              const float green,
                                              const float blue,
                                              const float alpha) {
  clearColor_[0] = red;
  clearColor_[1] = green;
  clearColor_[2] = blue;
  clearColor_[3] = alpha;
}
