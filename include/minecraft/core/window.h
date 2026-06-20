#pragma once

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Minecraft {
  /**
   * @brief Creates and manages the game window.
   */
  class Window {
  public:
    /// Called whenever the framebuffer size changes, e.g. resize or
    /// windowed <-> fullscreen toggle. Args are the new width/height in pixels.
    using ResizeCallback = std::function<void(int, int)>;

    /**
     * @brief Creates a window with the given size and title.
     * @param width Window width in pixels.
     * @param height Window height in pixels.
     * @param title Text shown in the window title bar.
     */
    Window(int width, int height, std::string title);

    ~Window();

    /**
     * @brief Sets up GLFW and opens the window.
     * @return true if successful, false if something went wrong.
     */
    bool init();

    /**
     * @brief Registers a callback fired on framebuffer resize (e.g. from
     * fullscreen toggles), in addition to the internal glViewport update.
     * @param callback Function taking the new (width, height) in pixels.
     */
    void setResizeCallback(ResizeCallback callback);

    /**
     * @brief Makes the window's rendering context current on this thread.
     */
    void makeContextCurrent() const;

    /**
     * @brief Handles window events.
     * Call this once per frame.
     */
    void pollEvents() const;

    /*
     * @brief Shows the window to the screen.
     * Call this once per frame.
     */
    void swapBuffers() const;

    /**
     * @brief Checks if the user wants to close the window.
     * @return true if the window should close.
     */
    [[nodiscard]] bool shouldClose() const;

    /**
     * @brief Gets the GLFW window handle.
     * @return Pointer to the GLFW window.
     */
    [[nodiscard]] GLFWwindow *getWindowHandle() const;

  private:
    int         width_  = 800;
    int         height_ = 600;
    std::string title_  = "Minecraft";

    GLFWwindow    *windowHandle_   = nullptr;
    ResizeCallback resizeCallback_ = nullptr;
  };
} // namespace Minecraft
