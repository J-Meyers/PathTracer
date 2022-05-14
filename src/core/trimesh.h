#pragma once
#include "scene_object.h"
#include <glm/vec3.hpp>

class Triangle : public SceneObject {
public:
  Triangle(Scene *s, std::unique_ptr<Material> m, const glm::dvec3 *vertices)
      : SceneObject(s, std::move(m)) {
    for (int i = 0; i < 3; i++) {
      this->verts[i] = vertices[i];
    }

    generateNormal();
  }

  void computeBoundingBox() override;
  [[nodiscard]] std::optional<ISect> intersect(const Ray &ray) const override;

protected:
  glm::dvec3 verts[3];
  glm::dvec3 normal;

  void generateNormal();
  bool intersectPlane(const glm::dvec3 &p, const glm::dvec3 &dir, double &t,
                      glm::dvec3 &i_p) const;
};

// class Triangle : public SceneObject {
// public:
//   Sphere(Scene *s, Material *m) : SceneObject(s, m){};
//
//   BoundingBox computeLocalBoundingBox() override;
//
// protected:
//   [[nodiscard]] std::optional<ISect>
//   intersectLocal(const Ray &ray) const override;
// };