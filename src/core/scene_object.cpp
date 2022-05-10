
#include "scene_object.h"
#include "geometry/ray.h"
#include "isect.h"
#include <optional>

// Copy-pasted then modified from ray tracer

std::optional<ISect> Geometry::intersect(Ray &r) const {
    double tmin, tmax;
    if (!(bounding_box_.intersect(r, tmin, tmax)))
        return std::nullopt;
    // Transform the ray into the object's local coordinate space
    glm::dvec3 pos = transform_node_->globalToLocal(r.getPos());
    glm::dvec3 dir = transform_node_->globalToLocal(r.getPos() +
                                                    r.getDir()) -
                     pos;
    double length = glm::length(dir);
    dir = glm::normalize(dir);
    // Backup World pos/dir, and switch to local pos/dir
    glm::dvec3 Wpos = r.getPos();
    glm::dvec3 Wdir = r.getDir();
    r.setPos(pos);
    r.setDir(dir);

    auto i = intersectLocal(r);

    // Restore World pos/dir
    r.setPos(Wpos);
    r.setDir(Wdir);

    if (i.has_value()) {
        // Transform the intersection point & normal returned back into
        // global space.
        i->setN(transform_node_->localToGlobalNormal(i->getN()));
        i->setT(i->getT() / length);
    }
    return i;
}

void Geometry::computeBoundingBox() {
    // take the object's local bounding box, transform all 8 points on it,
    // and use those to find a new bounding box.

    BoundingBox localBounds = computeLocalBoundingBox();

    glm::dvec3 min = localBounds.getMin();
    glm::dvec3 max = localBounds.getMax();

    glm::dvec4 v, newMax, newMin;

    v = transform_node_->localToGlobal(
            glm::dvec4(min[0], min[1], min[2], 1));
    newMax = v;
    newMin = v;
    v = transform_node_->localToGlobal(
            glm::dvec4(max[0], min[1], min[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);
    v = transform_node_->localToGlobal(
            glm::dvec4(min[0], max[1], min[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);
    v = transform_node_->localToGlobal(
            glm::dvec4(max[0], max[1], min[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);
    v = transform_node_->localToGlobal(
            glm::dvec4(min[0], min[1], max[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);
    v = transform_node_->localToGlobal(
            glm::dvec4(max[0], min[1], max[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);
    v = transform_node_->localToGlobal(
            glm::dvec4(min[0], max[1], max[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);
    v = transform_node_->localToGlobal(
            glm::dvec4(max[0], max[1], max[2], 1));
    newMax = glm::max(newMax, v);
    newMin = glm::min(newMin, v);

    bounding_box_.setMax(glm::dvec3(newMax));
    bounding_box_.setMin(glm::dvec3(newMin));
}