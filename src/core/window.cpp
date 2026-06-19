#include "minecraft/core/window.h"

#include <GLFW/glfw3.h>
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

bool Minecraft::Window::init() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW\n";
    return false;
  }

  // set opengl version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create window
  windowHandle_ =
      glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);

  if (!windowHandle_) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(windowHandle_);

  // initialise glad
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Failed to initialise GLAD\n";
    return false;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

  glViewport(0, 0, width_, height_);
  glEnable(GL_DEPTH_TEST);
  return true;
}

void Minecraft::Window::endFrame() const {
  if (!windowHandle_)
    return;

  glfwPollEvents();
  glfwSwapBuffers(windowHandle_);
}

bool Minecraft::Window::shouldClose() const {
  return glfwWindowShouldClose(windowHandle_);
}

GLFWwindow *Minecraft::Window::getWindowHandle() const {
  return windowHandle_;
}
