#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <memory>

#include "minecraft/renderer/i_renderer.h"
#include "opengl_shader.h"

namespace Minecraft {
  /**
   * @brief OpenGL implementation of the IRenderer interface.
   */
  class OpenGLRenderer : public IRenderer {
  public:
    OpenGLRenderer()           = default;
    ~OpenGLRenderer() override = default;

    /**
     * @brief Initializes the OpenGL renderer.
     * @return true if initialization succeeded, false otherwise.
     */
    bool init() override;

    /**
     * @brief Shuts down the OpenGL renderer and releases resources.
     */
    void shutdown() override;

    /**
     * @brief Renders the current frame using OpenGL.
     */
    void render() override;

    /**
     * @brief Clears the screen using OpenGL.
     */
    void clear() override;

    /**
     * @brief Sets the clear color for OpenGL.
     * @param red Red component (0.0 - 1.0).
     * @param green Green component (0.0 - 1.0).
     * @param blue Blue component (0.0 - 1.0).
     * @param alpha Alpha component (0.0 - 1.0).
     */
    void
    setClearColor(float red, float green, float blue, float alpha) override;

  private:
    float                         clearColor_[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLuint                        vao_           = 0;
    GLuint                        vbo_           = 0;
    std::unique_ptr<OpenGLShader> shader_;
    glm::mat4                     projection_;
  };
} // namespace Minecraft
