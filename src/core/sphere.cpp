#include "sphere.h"
#include "epsilon.h"
#include "isect.h"
#include <glm/gtx/norm.hpp>

BoundingBox Sphere::computeLocalBoundingBox() {
  BoundingBox b;
  b.setMin(glm::dvec3(-1.0, -1.0, -1.0));
  b.setMax(glm::dvec3(1.0, 1.0, 1.0));
  return b;
}

// precondition: ray direction is normalized
std::optional<ISect> Sphere::intersectLocal(const Ray &ray) const {

  glm::dvec3 v = -ray.getPos();
  double b = glm::dot(v, ray.getDir());
  double disc = b * b - glm::length2(v) + 1;

  if (disc < 0.0) {
    return std::nullopt;
  }

  disc = sqrt(disc);
  double t2 = b + disc;

  if (t2 <= EPSILON) {
    return std::nullopt;
  }

  double t1 = b - disc;
  ISect i;
  if (t1 > EPSILON) {
    i.setT(t1);
    i.setN(glm::normalize(ray(t1)));
  } else {
    i.setT(t2);
    i.setN(glm::normalize(ray(t2)));
  }
  i.setMat(material_);
  i.setSpectrum(material_->sample(ray));

  return i;
}
