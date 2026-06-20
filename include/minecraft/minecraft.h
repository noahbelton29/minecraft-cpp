#pragma once

#include <memory>
#include <string>

#include "core/window.h"
#include "renderer/i_renderer.h"
#include "renderer/i_shader.h"
#include "renderer/i_texture2d.h"
#include "renderer/i_vertex_array.h"
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
     * @param width  Window width in pixels.
     * @param height Window height in pixels.
     * @param title  Window title.
     * @param api    The rendering API to use.
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
    void
    initScene(); // builds geometry, shaders, and textures after GL is ready
    void update(const CameraController &controller, float dt);
    void submitScene() const; // queues all scene objects with the renderer

    Window                     window_;
    std::unique_ptr<IRenderer> renderer_;
    bool                       running_ = true;

    std::shared_ptr<IVertexArray> quadVao_;
    std::shared_ptr<IShader>      quadShader_;
    std::shared_ptr<ITexture2D>   quadTexture_;
  };

} // namespace Minecraft
