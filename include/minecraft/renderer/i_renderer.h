#pragma once

#include <memory>
#include "i_camera.h"

namespace Minecraft {
  /**
   * @brief Abstract interface for all renderer implementations.
   */
  class IRenderer {
  public:
    virtual ~IRenderer() = default;

    /**
     * @brief Initializes the renderer.
     * @return true if initialization succeeded, false otherwise.
     */
    virtual bool init() = 0;

    /**
     * @brief Shuts down the renderer and releases resources.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Renders the current frame.
     * Called once per frame from the main loop.
     */
    virtual void render() = 0;

    /**
     * @brief Clears the screen buffers.
     */
    virtual void clear() = 0;

    /**
     * @brief Sets the color used to clear the screen.
     * @param red Red component (0.0 - 1.0).
     * @param green Green component (0.0 - 1.0).
     * @param blue Blue component (0.0 - 1.0).
     * @param alpha Alpha component (0.0 - 1.0).
     */
    virtual void
    setClearColor(float red, float green, float blue, float alpha) = 0;

    /**
     * @brief Replaces the active camera.
     * @param camera The camera to render from.
     */
    virtual void setCamera(std::shared_ptr<ICamera> camera) = 0;
  };
} // namespace Minecraft
