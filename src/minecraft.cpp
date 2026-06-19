#include "minecraft/minecraft.h"

#include <iostream>

#include <GLFW/glfw3.h>

#include "minecraft/core/camera_controller.h"
#include "minecraft/core/input.h"
#include "minecraft/renderer/perspective_camera.h"
#include "minecraft/renderer/renderer_factory.h"

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

  Input::init(window_.getWindowHandle());
  CameraController controller(camera);

  float lastTime = static_cast<float>(glfwGetTime());

  while (running_ && !window_.shouldClose()) {
    const float now = static_cast<float>(glfwGetTime());
    const float dt  = now - lastTime;
    lastTime        = now;

    Input::update();
    update(controller, dt);

    renderer_->render();
    window_.pollEvents();
    window_.swapBuffers();
  }

  renderer_->shutdown();
}

void Minecraft::Minecraft::update(CameraController &controller, const float dt) {
  controller.update(dt);
}
