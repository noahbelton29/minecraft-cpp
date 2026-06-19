#include "minecraft/renderer/opengl/opengl_renderer.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "minecraft/renderer/opengl/opengl_index_buffer.h"
#include "minecraft/renderer/opengl/opengl_vertex_array.h"
#include "minecraft/renderer/opengl/opengl_vertex_buffer.h"
#include "minecraft/renderer/shader_factory.h"
#include "minecraft/util/file_utils.h"
#include "minecraft/util/shader_paths.h"

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

  constexpr float vertices[] = {
      -0.5f,
      -0.5f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      0.5f,
      -0.5f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      0.5f,
      0.0f,
      0.0f,
      0.0f,
      1.0f,
  };

  constexpr uint32_t indices[] = {0, 1, 2};

  const auto vb =
      std::make_shared<OpenGLVertexBuffer>(vertices, sizeof(vertices));
  const auto ib = std::make_shared<OpenGLIndexBuffer>(indices, 3);

  vertexArray_ = std::make_unique<OpenGLVertexArray>();
  vertexArray_->addVertexBuffer(vb,
                                {
                                    {ShaderDataType::Float3}, // position
                                    {ShaderDataType::Float3}, // color
                                });
  vertexArray_->setIndexBuffer(ib);

  const std::string vertexSrc = FileUtils::readFileToString(
      ShaderPaths::getVertexShaderPath(RendererAPI::OpenGL, "triangle"));
  const std::string fragmentSrc = FileUtils::readFileToString(
      ShaderPaths::getFragmentShaderPath(RendererAPI::OpenGL, "triangle"));

  shader_ = ShaderFactory::create(RendererAPI::OpenGL, vertexSrc, fragmentSrc);
  return true;
}

void Minecraft::OpenGLRenderer::shutdown() {
}

void Minecraft::OpenGLRenderer::render() {
  setClearColor(0.1f, 0.9f, 1.0f, 1.0f);
  clear();

  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  const float aspect = viewport[3] != 0 ? static_cast<float>(viewport[2]) /
                                              static_cast<float>(viewport[3])
                                        : 1.0f;

  projection_ =
      aspect >= 1.0f
          ? glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f)
          : glm::ortho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);

  shader_->bind();
  const int location =
      glGetUniformLocation(shader_->getNativeHandle(), "uProjection");
  glUniformMatrix4fv(location, 1, GL_FALSE, &projection_[0][0]);

  vertexArray_->bind();
  glDrawElements(GL_TRIANGLES,
                 static_cast<GLsizei>(vertexArray_->indexBuffer()->count()),
                 GL_UNSIGNED_INT,
                 nullptr);
  vertexArray_->unbind();
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
