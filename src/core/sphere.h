#pragma once
#include "scene_object.h"

class Sphere : public SceneObject {
public:
  Sphere(Scene *s, Material *m) : SceneObject(s, m){};

  BoundingBox computeLocalBoundingBox() override;

protected:
  [[nodiscard]] std::optional<ISect>
  intersectLocal(const Ray &ray) const override;
};
