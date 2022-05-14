#pragma once

#include "geometry/bbox.h"
#include "geometry/ray.h"
#include "material.h"
#include <memory>
#include <optional>

class Scene;
class ISect;

class SceneElement {
public:
  virtual ~SceneElement() = default;

  [[nodiscard]] Scene *getScene() const { return scene_; }

protected:
  explicit SceneElement(Scene *s) : scene_(s) {}

  Scene *scene_; // Not using reference so object can be copied
};

class Geometry : public SceneElement {
public:
  explicit Geometry(Scene *s) : SceneElement(s) {}

  [[nodiscard]] virtual std::optional<ISect>
  intersect(const Ray &ray) const = 0;

  virtual void computeBoundingBox() = 0;

  [[nodiscard]] const BoundingBox &getBoundingBox() const {
    return bounding_box_;
  }

protected:
  BoundingBox bounding_box_;
};

class SceneObject : public Geometry {
public:
  [[nodiscard]] const Material &getMaterial() const { return *material_; }

  void setMaterial(std::unique_ptr<Material> m) { material_ = std::move(m); }

protected:
  SceneObject(Scene *s, std::unique_ptr<Material> m)
      : Geometry(s), material_(std::move(m)) {}
  std::unique_ptr<Material> material_;
};
