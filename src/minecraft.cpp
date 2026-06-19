#include "minecraft/minecraft.h"
#include <iostream>
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

  while (running_ && !window_.shouldClose()) {
    update();
    renderer_->render();
    window_.pollEvents();
    window_.swapBuffers();
  }

  renderer_->shutdown();
}

void Minecraft::Minecraft::update() {
}
