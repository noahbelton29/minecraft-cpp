#include "minecraft/renderer/opengl/opengl_renderer.h"

#include <GLFW/glfw3.h>
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
  setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  clear();

  shader_->bind();

  if (camera_)
    shader_->setUniform("uViewProjection", camera_->viewProjectionMatrix());

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

void Minecraft::OpenGLRenderer::setCamera(std::shared_ptr<ICamera> camera) {
  camera_ = std::move(camera);
}
