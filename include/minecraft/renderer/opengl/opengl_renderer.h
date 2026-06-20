#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>

#include "minecraft/renderer/i_camera.h"
#include "minecraft/renderer/i_renderer.h"

namespace Minecraft {

  /**
   * @brief OpenGL implementation of IRenderer.
   */
  class OpenGLRenderer : public IRenderer {
  public:
    OpenGLRenderer()           = default;
    ~OpenGLRenderer() override = default;

    /**
     * @brief Initializes the OpenGL renderer.
     *
     * Loads OpenGL function pointers, enables depth testing, and sets the
     * viewport. Does not create any geometry — callers submit that via
     * submit().
     *
     * @return true if initialization succeeded, false otherwise.
     */
    bool init() override;

    /**
     * @brief Shuts down the OpenGL renderer and releases resources.
     */
    void shutdown() override;

    /**
     * @brief Flushes all queued render commands, then clears the queue.
     */
    void render() override;

    /**
     * @brief Clears the screen using OpenGL.
     */
    void clear() override;

    /**
     * @brief Sets the clear color for OpenGL.
     * @param red   Red component (0.0 - 1.0).
     * @param green Green component (0.0 - 1.0).
     * @param blue  Blue component (0.0 - 1.0).
     * @param alpha Alpha component (0.0 - 1.0).
     */
    void
    setClearColor(float red, float green, float blue, float alpha) override;

    /**
     * @brief Replaces the active camera.
     * @param camera The camera to render from.
     */
    void setCamera(std::shared_ptr<ICamera> camera) override;

    /**
     * @brief Queues a draw call for the current frame.
     * @param vertexArray Geometry to draw.
     * @param shader      Shader to use.
     * @param transform   Model matrix for this object.
     */
    void submit(std::shared_ptr<IVertexArray> vertexArray,
                std::shared_ptr<IShader>      shader,
                const glm::mat4              &transform) override;

  private:
    float clearColor_[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    std::shared_ptr<ICamera>   camera_;
    std::vector<RenderCommand> commands_; // flushed each frame in render()
  };

} // namespace Minecraft
