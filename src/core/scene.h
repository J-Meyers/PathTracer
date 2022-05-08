#pragma once

#include "camera.h"
#include "geometry/transform_node.h"
#include "isect.h"
#include "scene_object.h"
#include <optional>
#include <vector>
#include <memory>

class Scene {
public:
    TransformNode root_;

    void add(std::unique_ptr<Geometry> geometry);

    std::optional<ISect> intersect(Ray &ray) const;

    [[nodiscard]] const Camera &getCamera() const { return camera_; }

    Camera &getCamera() { return camera_; }

    [[nodiscard]] const BoundingBox &getBoundingBox() const { return bounding_box_; }

private:
    Camera camera_;

    BoundingBox bounding_box_;

    std::vector<std::unique_ptr<Geometry>> objects_;
};
