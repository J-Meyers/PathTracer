#pragma once

#include "geometry/bbox.h"
#include "geometry/ray.h"
#include "geometry/transform_node.h"
#include "isect.h"
#include "material.h"
#include <optional>

class Scene;

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

    std::optional<ISect> intersect(Ray &ray) const;

    virtual void computeBoundingBox();

    virtual BoundingBox computeLocalBoundingBox() = 0;

    [[nodiscard]] const BoundingBox &getBoundingBox() const { return bounding_box_; }

    void setTransform(TransformNode *transform) { transform_node_ = transform; }

protected:
    [[nodiscard]] virtual std::optional<ISect> intersectLocal(const Ray &ray) const = 0;

    BoundingBox bounding_box_;
    TransformNode *transform_node_ = nullptr;
};

class SceneObject : public Geometry {
public:
    [[nodiscard]] const Material &getMaterial() const { return *material_; }

    void setMaterial(std::unique_ptr<Material> m) { material_ = std::move(m); }

protected:
    SceneObject(Scene *s, Material *m) : Geometry(s), material_(m) {}

    std::unique_ptr<Material> material_;
};
