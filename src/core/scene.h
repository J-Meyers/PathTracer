#pragma once

#include "camera.h"
#include "geometry/transform_node.h"
#include "isect.h"
#include "scene_object.h"
#include <optional>
#include <vector>

class Scene {
public:
  TransformNode root_;

  void add(Geometry *geometry);

  std::optional<ISect> intersect(const Ray &ray) const;
  const Camera &getCamera() const { return camera_; }
  Camera &getCamera() { return camera_; }

  const BoundingBox &getBoundingBox() const { return bounding_box_; }

private:
  Camera camera_;

  BoundingBox bounding_box_;

  std::vector<std::unique_ptr<Geometry>> objects_;
};
