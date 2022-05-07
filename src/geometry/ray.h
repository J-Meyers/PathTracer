#pragma once

#include <glm/vec3.hpp>

class Ray {
  Ray(const glm::vec3& pos, const glm::vec3& dir) : pos_(pos), dir_(dir) {}


private:
  glm::vec3 pos_;
  glm::vec3 dir_;
};