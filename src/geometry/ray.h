#pragma once

#include <glm/vec3.hpp>

class Ray {
public:
  constexpr Ray(const glm::dvec3 &pos, const glm::dvec3 &dir)
      : pos_(pos), dir_(dir) {}

  [[nodiscard]] constexpr glm::dvec3 getPos() const { return pos_; }

  [[nodiscard]] constexpr glm::dvec3 getDir() const { return dir_; }

  void setPos(const glm::dvec3 &pos) { pos_ = pos; }

  void setDir(const glm::dvec3 &dir) { dir_ = dir; }

  [[nodiscard]] constexpr glm::dvec3 operator()(double t) const {
    return pos_ + t * dir_;
  }

private:
  glm::dvec3 pos_;
  glm::dvec3 dir_;
};