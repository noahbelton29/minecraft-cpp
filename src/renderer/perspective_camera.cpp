#include "minecraft/renderer/perspective_camera.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

Minecraft::PerspectiveCamera::PerspectiveCamera(const float fovDeg,
                                                const float aspect,
                                                const float nearClip,
                                                const float farClip) :
    fovDeg_(fovDeg), aspect_(aspect), nearClip_(nearClip), farClip_(farClip) {
  recalculate();
}

void Minecraft::PerspectiveCamera::setPosition(const glm::vec3 &position) {
  position_ = position;
  recalculate();
}

void Minecraft::PerspectiveCamera::setRotation(const float yaw, const float pitch) {
  yaw_   = yaw;
  pitch_ = std::clamp(pitch, -89.0f, 89.0f);
  recalculate();
}

void Minecraft::PerspectiveCamera::setAspect(const float aspect) {
  aspect_ = aspect;
  recalculate();
}

const glm::mat4 &Minecraft::PerspectiveCamera::viewMatrix() const {
  return view_;
}

const glm::mat4 &Minecraft::PerspectiveCamera::projectionMatrix() const {
  return projection_;
}

const glm::mat4 &Minecraft::PerspectiveCamera::viewProjectionMatrix() const {
  return viewProjection_;
}

const glm::vec3 &Minecraft::PerspectiveCamera::position() const {
  return position_;
}

float Minecraft::PerspectiveCamera::yaw() const {
  return yaw_;
}

float Minecraft::PerspectiveCamera::pitch() const {
  return pitch_;
}

void Minecraft::PerspectiveCamera::recalculate() {
  // derive forward vector from yaw and pitch
  const float yawRad   = glm::radians(yaw_);
  const float pitchRad = glm::radians(pitch_);

  glm::vec3 forward;
  forward.x = glm::cos(pitchRad) * glm::cos(yawRad);
  forward.y = glm::sin(pitchRad);
  forward.z = glm::cos(pitchRad) * glm::sin(yawRad);
  forward   = glm::normalize(forward);

  view_           = glm::lookAt(position_, position_ + forward, glm::vec3(0.0f, 1.0f, 0.0f));
  projection_     = glm::perspective(glm::radians(fovDeg_), aspect_, nearClip_, farClip_);
  viewProjection_ = projection_ * view_;
}
