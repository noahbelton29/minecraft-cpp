#pragma once

#include "minecraft/renderer/i_shader.h"

#include <glad/glad.h>
#include <string>

namespace Minecraft {
  /**
   * @brief OpenGL implementation of the IShader interface.
   */
  class OpenGLShader : public IShader {
  public:
    /**
     * @brief Compiles and links a shader from GLSL source code.
     * @param vertexSource Vertex shader source code.
     * @param fragmentSource Fragment shader source code.
     */
    OpenGLShader(const std::string &vertexSource,
                 const std::string &fragmentSource);

    ~OpenGLShader() override;
    /**
     * @brief Activates this shader for drawing.
     */
    void bind() override;
    /**
     * @brief Sets a float value on the shader.
     * @param name Name of the uniform in the shader code.
     * @param value Value to give it.
     */
    void setUniform(const std::string &, float) override;
    /**
     * @brief Gets the OpenGL program ID for this shader.
     * @return The shader program ID.
     */
    [[nodiscard]] GLuint getProgram() const;
    /**
     * @brief Gets the backend's native handle for this shader.
     * @return The OpenGL program ID.
     */
    [[nodiscard]] unsigned int getNativeHandle() const override;

  private:
    GLuint program_ = 0;
    /**
     * @brief Compiles a single shader stage from source.
     * @param type The shader stage type.
     * @param source GLSL source code for the shader.
     * @return The compiled shader ID.
     */
    GLuint compileShader(GLenum type, const std::string &source);
  };
} // namespace Minecraft
