#include "camera.h"

#include "geometry/orthonormal_basis.h"
#include <cmath>
#include <iostream>

Camera::Camera(const glm::vec3 &eye, const glm::vec3 &look, const glm::vec3 &up,
               int height, int width, double vertical_fov)
    : eye_(eye), rotation_(OrthonormalBasis::fromZY(look, up)), width_(width),
      height_(height), aspect_ratio_(static_cast<double>(width) / height),
      height_inv_(1.0 / height), width_inv_(1.0 / width),
      distance_to_plane_(1.0 / std::tan(vertical_fov)) {}

Ray Camera::rayThroughPixel(int pixel_x, int pixel_y) const {
  pixel_x -= width_ / 2;
  pixel_y -= height_ / 2;
  double x = (pixel_x + .5) * width_inv_;
  double y = (pixel_y + .5) * height_inv_;
  return rayThroughPoint(x, y);
}

Ray Camera::rayThroughPoint(double x, double y) const {
  // x and y are in [-0.5, -0.5]
  glm::dvec3 point{-x * aspect_ratio_, -y, distance_to_plane_};
  glm::dvec3 dir = glm::normalize(rotation_ * point);
  return Ray(eye_, dir);
}
