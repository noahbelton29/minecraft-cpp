#include "minecraft/renderer/opengl/opengl_shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLuint Minecraft::OpenGLShader::compileShader(const GLenum       type,
                                              const std::string &source) {
  const GLuint shader = glCreateShader(type);

  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
    std::cerr << "Shader compilation failed:\n" << infoLog << '\n';
  }

  return shader;
}

Minecraft::OpenGLShader::OpenGLShader(const std::string &vertexSource,
                                      const std::string &fragmentSource) {
  const GLuint vertexShader   = compileShader(GL_VERTEX_SHADER,   vertexSource);
  const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

  program_ = glCreateProgram();
  glAttachShader(program_, vertexShader);
  glAttachShader(program_, fragmentShader);
  glLinkProgram(program_);

  GLint success;
  glGetProgramiv(program_, GL_LINK_STATUS, &success);

  if (!success) {
    char infoLog[1024];
    glGetProgramInfoLog(program_, sizeof(infoLog), nullptr, infoLog);
    std::cerr << "Program linking failed:\n" << infoLog << '\n';
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Minecraft::OpenGLShader::~OpenGLShader() {
  if (program_)
    glDeleteProgram(program_);
}

void Minecraft::OpenGLShader::bind() {
  glUseProgram(program_);
}

GLuint Minecraft::OpenGLShader::getProgram() const {
  return program_;
}

unsigned int Minecraft::OpenGLShader::getNativeHandle() const {
  return program_;
}

void Minecraft::OpenGLShader::setUniform(const std::string &name,
                                         const float        value) {
  if (const GLint loc = glGetUniformLocation(program_, name.c_str()); loc != -1)
    glUniform1f(loc, value);
}

void Minecraft::OpenGLShader::setUniform(const std::string &name,
                                         const int          value) {
  if (const GLint loc = glGetUniformLocation(program_, name.c_str()); loc != -1)
    glUniform1i(loc, value);
}

void Minecraft::OpenGLShader::setUniform(const std::string &name,
                                         const glm::mat4   &value) {
  if (const GLint loc = glGetUniformLocation(program_, name.c_str()); loc != -1)
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}
