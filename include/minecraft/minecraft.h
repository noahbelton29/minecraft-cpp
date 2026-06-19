#pragma once

#include <memory>
#include <string>

#include "core/window.h"
#include "renderer/i_renderer.h"
#include "renderer/renderer_api.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace Minecraft {
  class CameraController;

  /**
   * @brief The main Minecraft game application.
   */
  class Minecraft {
  public:
    /**
     * @brief Creates the game with a window.
     * @param width Window width in pixels.
     * @param height Window height in pixels.
     * @param title Window title.
     * @param api The rendering API to use.
     */
    explicit Minecraft(int         width  = WINDOW_WIDTH,
                       int         height = WINDOW_HEIGHT,
                       std::string title  = "Minecraft",
                       RendererAPI api    = RendererAPI::OpenGL);
    ~Minecraft();

    /**
     * @brief Starts the game loop.
     * Keeps running until the window closes.
     */
    void run();

  private:
    void update(CameraController &controller,
                float             dt); // updates game logic each frame

    Window                     window_;
    std::unique_ptr<IRenderer> renderer_;
    bool                       running_ = true;
  };
} // namespace Minecraft
