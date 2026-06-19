#pragma once

#include "core/window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace Minecraft {
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
     */
    explicit Minecraft(int         width  = WINDOW_WIDTH,
                       int         height = WINDOW_HEIGHT,
                       std::string title  = "Minecraft");
    ~Minecraft();

    /**
     * @brief Starts the game loop.
     * Keeps running until the window closes.
     */
    void run();

  private:
    void update(); // Updates game logic each frame
    void render(); // Draws everything each frame

    Window window_;
    bool   running_ = true;
  };
} // namespace Minecraft
