#pragma once

#include <glm/mat4x4.hpp>
#include <memory>

#include "i_camera.h"
#include "i_shader.h"
#include "i_vertex_array.h"

namespace Minecraft {
  /**
   * @brief A single draw call: geometry + shader + model transform.
   */
  struct RenderCommand {
    std::shared_ptr<IVertexArray> vertexArray;
    std::shared_ptr<IShader>      shader;
    glm::mat4                     transform;
  };

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
     * @brief Renders all submitted commands for this frame, then clears the
     * queue. Called once per frame from the main loop.
     */
    virtual void render() = 0;

    /**
     * @brief Clears the screen buffers.
     */
    virtual void clear() = 0;

    /**
     * @brief Sets the color used to clear the screen.
     * @param red   Red component (0.0 - 1.0).
     * @param green Green component (0.0 - 1.0).
     * @param blue  Blue component (0.0 - 1.0).
     * @param alpha Alpha component (0.0 - 1.0).
     */
    virtual void
    setClearColor(float red, float green, float blue, float alpha) = 0;

    /**
     * @brief Replaces the active camera.
     * @param camera The camera to render from.
     */
    virtual void setCamera(std::shared_ptr<ICamera> camera) = 0;

    /**
     * @brief Queues a draw call for this frame.
     *
     * The renderer uploads uViewProjection and uTransform uniforms
     * automatically before issuing the draw call. All submitted commands are
     * flushed during render() and the queue is reset.
     *
     * @param vertexArray Geometry to draw.
     * @param shader      Shader to use.
     * @param transform   Model matrix for this object.
     */
    virtual void submit(std::shared_ptr<IVertexArray> vertexArray,
                        std::shared_ptr<IShader>      shader,
                        const glm::mat4              &transform) = 0;
  };

} // namespace Minecraft
