#include "minecraft/renderer/opengl/opengl_renderer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "minecraft/renderer/shader_factory.h"
#include "minecraft/renderer/shader_paths.h"
#include "minecraft/util/file_utils.h"

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

  constexpr float vertices[] = {-0.5f,
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
                                1.0f};

  // VAO
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  // VBO
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position (location = 0)
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        6 * sizeof(float),
                        static_cast<void *>(nullptr));
  glEnableVertexAttribArray(0);

  // color (location = 1)
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        6 * sizeof(float),
                        reinterpret_cast<void *>(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

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

  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
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
