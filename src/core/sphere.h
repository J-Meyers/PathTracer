#pragma once
#include "scene_object.h"
#include <glm/vec3.hpp>

class Sphere : public SceneObject {
public:
  Sphere(Scene *s, std::unique_ptr<Material> m, const glm::dvec3 &center,
         double r)
      : SceneObject(s, std::move(m)), c_{center}, r_{r} {};

  void computeBoundingBox() override;
  [[nodiscard]] std::optional<ISect> intersect(const Ray &ray) const override;

private:
  glm::dvec3 c_;
  double r_;
};
