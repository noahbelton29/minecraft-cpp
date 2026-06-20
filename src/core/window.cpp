#include "minecraft/core/window.h"
#include <iostream>
#include <utility>

Minecraft::Window::Window(const int   width,
                          const int   height,
                          std::string title) :
    width_(width), height_(height), title_(std::move(title)) {
}

Minecraft::Window::~Window() {
  if (windowHandle_) {
    glfwDestroyWindow(windowHandle_);
    windowHandle_ = nullptr;
  }
  glfwTerminate();
}

void Minecraft::Window::makeContextCurrent() const {
  glfwMakeContextCurrent(windowHandle_);
  glfwSwapInterval(0);
}

bool Minecraft::Window::init() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW\n";
    return false;
  }

  // Create window
  windowHandle_ =
      glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
  if (!windowHandle_) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return false;
  }

  // Let the static GLFW callback reach back into this instance.
  glfwSetWindowUserPointer(windowHandle_, this);

  glfwSetFramebufferSizeCallback(
      windowHandle_, [](GLFWwindow *handle, const int width, const int height) {
        glViewport(0, 0, width, height);

        auto *self = static_cast<Window *>(glfwGetWindowUserPointer(handle));
        if (self) {
          self->width_  = width;
          self->height_ = height;
          if (self->resizeCallback_) {
            self->resizeCallback_(width, height);
          }
        }
      });

  return true;
}

void Minecraft::Window::setResizeCallback(ResizeCallback callback) {
  resizeCallback_ = std::move(callback);
}

void Minecraft::Window::pollEvents() const {
  if (!windowHandle_)
    return;

  glfwPollEvents();
}

void Minecraft::Window::swapBuffers() const {
  if (!windowHandle_)
    return;

  glfwSwapBuffers(windowHandle_);
}

bool Minecraft::Window::shouldClose() const {
  return glfwWindowShouldClose(windowHandle_);
}

GLFWwindow *Minecraft::Window::getWindowHandle() const {
  return windowHandle_;
}
