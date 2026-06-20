#include "minecraft/minecraft.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "minecraft/core/camera_controller.h"
#include "minecraft/core/input.h"
#include "minecraft/renderer/opengl/opengl_index_buffer.h"
#include "minecraft/renderer/opengl/opengl_texture2d.h"
#include "minecraft/renderer/opengl/opengl_vertex_array.h"
#include "minecraft/renderer/opengl/opengl_vertex_buffer.h"
#include "minecraft/renderer/perspective_camera.h"
#include "minecraft/renderer/renderer_factory.h"
#include "minecraft/renderer/shader_factory.h"
#include "minecraft/util/file_utils.h"
#include "minecraft/util/shader_paths.h"

Minecraft::Minecraft::Minecraft(const int         width,
                                const int         height,
                                std::string       title,
                                const RendererAPI api) :
    window_(width, height, std::move(title)),
    renderer_(RendererFactory::create(api)) {

  if (!renderer_) {
    std::cerr << "Failed to create renderer\n";
    running_ = false;
  }
}

Minecraft::Minecraft::~Minecraft() = default;

void Minecraft::Minecraft::run() {
  if (!window_.init()) {
    std::cerr << "Failed to initialize window\n";
    running_ = false;
    return;
  }

  window_.makeContextCurrent();

  if (!renderer_ || !renderer_->init()) {
    std::cerr << "Failed to initialize renderer\n";
    running_ = false;
    return;
  }

  auto camera = std::make_shared<PerspectiveCamera>(
      70.0f,
      static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
      0.1f,
      1000.0f);
  camera->setPosition({0.0f, 0.0f, 3.0f});
  renderer_->setCamera(camera);

  window_.setResizeCallback([camera](const int width, const int height) {
    if (height <= 0) {
      return;
    }
    camera->setAspect(static_cast<float>(width) / static_cast<float>(height));
  });

  Input::init(window_.getWindowHandle());
  const CameraController controller(camera);

  initScene();

  auto lastTime = static_cast<float>(glfwGetTime());

  while (running_ && !window_.shouldClose()) {
    const auto  now = static_cast<float>(glfwGetTime());
    const float dt  = now - lastTime;
    lastTime        = now;

    Input::update();
    update(controller, dt);

    submitScene();
    renderer_->render();

    window_.pollEvents();
    window_.swapBuffers();
  }

  renderer_->shutdown();
}

void Minecraft::Minecraft::initScene() {
  constexpr float vertices[] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom-left
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom-right
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top-right
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top-left
  };

  constexpr uint32_t indices[] = {
      0,
      1,
      2,
      2,
      3,
      0,
  };

  const auto vb =
      std::make_shared<OpenGLVertexBuffer>(vertices, sizeof(vertices));
  const auto ib = std::make_shared<OpenGLIndexBuffer>(indices, 6);

  quadVao_ = std::make_shared<OpenGLVertexArray>();
  quadVao_->addVertexBuffer(vb,
                            {
                                {ShaderDataType::Float3}, // position
                                {ShaderDataType::Float2}, // uv
                            });
  quadVao_->setIndexBuffer(ib);

  const std::string vertSrc = FileUtils::readFileToString(
      ShaderPaths::getVertexShaderPath(RendererAPI::OpenGL, "quad"));
  const std::string fragSrc = FileUtils::readFileToString(
      ShaderPaths::getFragmentShaderPath(RendererAPI::OpenGL, "quad"));

  quadShader_ = ShaderFactory::create(RendererAPI::OpenGL, vertSrc, fragSrc);

  quadTexture_ =
      std::make_shared<OpenGLTexture2D>("resources/textures/test.png");

  quadShader_->bind();
  quadShader_->setUniform("uTexture", 0);
}

void Minecraft::Minecraft::submitScene() const {
  quadTexture_->bind(0);
  renderer_->submit(quadVao_, quadShader_, glm::mat4(1.0f));
}

void Minecraft::Minecraft::update(const CameraController &controller,
                                  const float             dt) {
  controller.update(dt);
}
