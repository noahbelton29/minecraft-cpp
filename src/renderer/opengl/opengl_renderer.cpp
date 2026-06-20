#include "minecraft/renderer/opengl/opengl_renderer.h"

#include <GLFW/glfw3.h>
#include <iostream>

bool Minecraft::OpenGLRenderer::init() {
  std::cout << "Initializing OpenGL Renderer\n";

  if (!gladLoadGL()) {
    std::cerr << "Failed to load OpenGL functions\n";
    return false;
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

  int fbWidth, fbHeight;
  glfwGetFramebufferSize(glfwGetCurrentContext(), &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);

  glEnable(GL_DEPTH_TEST);
  return true;
}

void Minecraft::OpenGLRenderer::shutdown() {
  commands_.clear();
}

void Minecraft::OpenGLRenderer::render() {
  setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  clear();

  const glm::mat4 &vp =
      camera_ ? camera_->viewProjectionMatrix() : glm::mat4(1.0f);

  for (const auto &[vertexArray, shader, transform]: commands_) {
    shader->bind();
    shader->setUniform("uViewProjection", vp);
    shader->setUniform("uTransform", transform);

    vertexArray->bind();
    glDrawElements(GL_TRIANGLES,
                   static_cast<GLsizei>(vertexArray->indexBuffer()->count()),
                   GL_UNSIGNED_INT,
                   nullptr);
    vertexArray->unbind();
  }

  commands_.clear();
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

void Minecraft::OpenGLRenderer::setCamera(std::shared_ptr<ICamera> camera) {
  camera_ = std::move(camera);
}

void Minecraft::OpenGLRenderer::submit(
    std::shared_ptr<IVertexArray> vertexArray,
    std::shared_ptr<IShader>      shader,
    const glm::mat4              &transform) {
  commands_.push_back({std::move(vertexArray), std::move(shader), transform});
}
