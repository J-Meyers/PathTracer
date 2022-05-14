#pragma once

#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

#include "geometry/ray.h"

class Camera {
public:
  Camera(const glm::vec3 &eye, const glm::vec3 &look, const glm::vec3 &up,
         int height, int width, double vertical_fov, double aperture = 0,
         double focal_length = 0);

  [[nodiscard]] Ray rayThroughPixel(int x, int y) const;

private:
  [[nodiscard]] Ray rayThroughPoint(double x, double y) const;
  [[nodiscard]] Ray randRayThroughPoint(double x, double y) const;

  glm::dvec3 eye_;
  glm::dmat3 rotation_;
  int width_;
  int height_;
  double aspect_ratio_;
  double height_inv_;
  double width_inv_;
  double distance_to_plane_;
  double aperture_;
  double focal_length_;
};
