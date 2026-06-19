#include "minecraft/minecraft.h"
#include <iostream>

Minecraft::Minecraft::Minecraft(const int   width,
                                const int   height,
                                std::string title) :
    window_(width, height, std::move(title)) {
}

Minecraft::Minecraft::~Minecraft() = default;

void Minecraft::Minecraft::run() {
  if (!window_.init()) {
    std::cerr << "Failed to initialize window\n";
    running_ = false;
    return;
  }

  while (running_ && !window_.shouldClose()) {
    update();
    render();
    window_.endFrame();
  }
}

void Minecraft::Minecraft::update() {
}

void Minecraft::Minecraft::render() {
  glClearColor(0.1f, 0.5f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
