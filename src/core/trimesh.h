#pragma once
#include "scene_object.h"
#include <glm/vec3.hpp>

class Triangle : public SceneObject {
public:
  Triangle(Scene *s, Material *m, const glm::dvec3 *vertices)
      : SceneObject(s, m) {
    for (int i = 0; i < 3; i++) {
      this->verts[i] = vertices[i];
    }

    generateNormal();
  }

  BoundingBox computeLocalBoundingBox() override;

protected:
  glm::dvec3 verts[3];
  glm::dvec3 normal;

  void generateNormal();
  bool intersectPlane(const glm::dvec3 &p, const glm::dvec3 &dir, double &t,
                      glm::dvec3 &i_p) const;
  [[nodiscard]] std::optional<ISect>
  intersectLocal(const Ray &ray) const override;
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