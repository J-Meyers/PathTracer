#include "sphere.h"
#include "isect.h"
#include <glm/gtx/norm.hpp>

void Sphere::computeBoundingBox() {
  bounding_box_.setMin(glm::dvec3(-1.0, -1.0, -1.0));
  bounding_box_.setMax(glm::dvec3(1.0, 1.0, 1.0));
}

// precondition: ray direction is normalized
std::optional<ISect> Sphere::intersect(const Ray &ray) const {
  double tmin, tmax;
  if (!bounding_box_.intersect(ray, tmin, tmax)) {
    return std::nullopt;
  }

  glm::dvec3 v = c_ - ray.getPos();
  double b = glm::dot(v, ray.getDir());
  double disc = b * b - glm::length2(v) + r_ * r_;

  if (disc < 0.0) {
    return std::nullopt;
  }

  disc = sqrt(disc);
  double t2 = b + disc;

  if (t2 <= EPSILON) {
    return std::nullopt;
  }

  double t1 = b - disc;
  ISect i{};
  auto t = t1 > EPSILON ? t1 : t2;
  i.setT(t);
  i.setPt(ray(t));
  i.setN(glm::normalize(i.getPt() - c_));
  i.setMat(material_.get());

  return i;
}
