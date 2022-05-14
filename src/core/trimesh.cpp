#include "trimesh.h"
#include "core/isect.h"
#include <glm/geometric.hpp>

// ASSUMPTIONS: winding order of triangles is consistent, they aren't degenerate
void Triangle::generateNormal() {
  glm::dvec3 v01 = verts[1] - verts[0];
  glm::dvec3 v02 = verts[2] - verts[0];
  glm::dvec3 v21 = verts[1] - verts[2];

  assert(glm::length(v01) != 0.0 && glm::length(v02) != 0.0 &&
         glm::length(v21) != 0.0);

  normal = glm::cross(v01, v02);
  normal = glm::normalize(normal);
}

// local coordinates are just global coords for triangles
void Triangle::computeBoundingBox() {
  bounding_box_.setMin(glm::min(glm::min(verts[0], verts[1]), verts[2]));
  bounding_box_.setMax(glm::max(glm::max(verts[0], verts[1]), verts[2]));
}

bool Triangle::intersectPlane(const glm::dvec3 &p, const glm::dvec3 &dir,
                              double &t, glm::dvec3 &i_p) const {
  const auto &a = verts[0];
  // Is on plane
  double denominator = glm::dot(dir, normal);
  if (denominator == 0) {
    return false;
  }
  double numerator = glm::dot((a - p), normal);
  t = numerator / denominator;
  if (t < 0) {
    return false;
  }
  i_p = p + dir * t;
  return true;
}

[[nodiscard]] std::optional<ISect> Triangle::intersect(const Ray &ray) const {
  double tmin, tmax;
  if (!bounding_box_.intersect(ray, tmin, tmax)) {
    return std::nullopt;
  }
  glm::dvec3 i_p;
  double t;
  if (intersectPlane(ray.getPos(), ray.getDir(), t, i_p)) {
    const auto &a = verts[0];
    const auto &b = verts[1];
    const auto &c = verts[2];

    auto ba = glm::dot(glm::cross((b - a), (i_p - a)), normal);
    if (ba < 0) {
      return std::nullopt;
    }

    auto ac = glm::dot(glm::cross((a - c), (i_p - c)), normal);
    if (ac < 0) {
      return std::nullopt;
    }

    double face_area = glm::dot(glm::cross(b - a, c - a), normal);

    auto u = ac / face_area;
    auto v = ba / face_area;
    if (1 - u - v < 0) {
      return std::nullopt;
    }

    ISect i;
    i.setT(t);
    i.setPt(ray(t));
    i.setN(normal);
    i.setMat(material_);
    return i;
  }

  return std::nullopt;
}
