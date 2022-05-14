#include "camera.h"

#include "geometry/light_functions.h"
#include "geometry/orthonormal_basis.h"
#include <cmath>
#include <iostream>

using namespace light_functions;

Camera::Camera(const glm::vec3 &eye, const glm::vec3 &look, const glm::vec3 &up,
               int height, int width, double vertical_fov, double aperture,
               double focal_length)
    : eye_(eye), rotation_(OrthonormalBasis::fromZY(look, up)), width_(width),
      height_(height), aspect_ratio_(static_cast<double>(width) / height),
      height_inv_(1.0 / height), width_inv_(1.0 / width),
      distance_to_plane_(1.0 / std::tan(vertical_fov)), aperture_(aperture),
      focal_length_(focal_length) {}

Ray Camera::rayThroughPixel(int pixel_x, int pixel_y) const {
  pixel_x -= width_ / 2;
  pixel_y -= height_ / 2;
  double x = (pixel_x + .5) * width_inv_;
  double y = (pixel_y + .5) * height_inv_;
  if (aperture_ > 0.0) {
    return randRayThroughPoint(x, y);
  }
  return rayThroughPoint(x, y);
}

/*

 auto focalPoint = centre_ + direction * focalDistance_;
   std::uniform_real_distribution<> angleDist(0, 2 * M_PI);
   std::uniform_real_distribution<> radiusDist(0, apertureRadius_);
   auto angle = angleDist(rng);
   auto radius = radiusDist(rng);
   auto origin = centre_ + (axis_.x() * cos(angle) * radius)
                 + (axis_.y() * sin(angle) * radius);
   return Ray::fromTwoPoints(origin, focalPoint);

 */

Ray Camera::rayThroughPoint(double x, double y) const {
  // x and y are in [-0.5, -0.5]
  glm::dvec3 point{-x * aspect_ratio_, -y, distance_to_plane_};
  glm::dvec3 dir = glm::normalize(rotation_ * point);
  return Ray(eye_, dir);
}

Ray Camera::randRayThroughPoint(double x, double y) const {
  // x and y are in [-0.5, -0.5]
  glm::dvec3 point{-x * aspect_ratio_, -y, distance_to_plane_};
  glm::dvec3 desired_dir = glm::normalize(rotation_ * point);
  point = eye_ + desired_dir * focal_length_;

  glm::dvec2 randOffset =
      sampleUnitDisk(random_uniform(), random_uniform()) * aperture_;
  glm::dvec3 effectiveEye = eye_ + glm::dvec3{randOffset.x, randOffset.y, 0};
  glm::dvec3 dir = glm::normalize(point - effectiveEye); // real dir

  return {effectiveEye, dir};
}