#pragma once

#include "camera.h"
#include "geometry/transform_node.h"
#include "isect.h"
#include "scene_object.h"
#include <memory>
#include <optional>
#include <vector>

class Scene {
public:
  Scene(const Camera &camera) : camera_(camera) {}
  TransformNodeRoot root_;

  void add(std::unique_ptr<Geometry> geometry);

  std::optional<ISect> intersect(const Ray &ray) const;

  [[nodiscard]] const Camera &getCamera() const { return camera_; }

  Camera &getCamera() { return camera_; }

  [[nodiscard]] const BoundingBox &getBoundingBox() const {
    return bounding_box_;
  }

  void setBackgroundRadiance(const Spectrum &s) { background_radiance_ = s; }

  [[nodiscard]] Spectrum backgroundRadiance(const Ray &r) const;

private:
  Camera camera_;

  BoundingBox bounding_box_;

  std::vector<std::unique_ptr<Geometry>> objects_;

  Spectrum background_radiance_;
};
