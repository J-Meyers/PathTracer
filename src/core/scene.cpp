#include "scene.h"
#include <numeric>

void Scene::add(std::unique_ptr<Geometry> geometry) {
    objects_.push_back(std::move(geometry));
}

std::optional<ISect> Scene::intersect(Ray &ray) const {
    std::optional<ISect> res;
    for (const auto &object: objects_) {
        if (auto curr = object->intersect(ray); (!res || (curr && curr->getT() < res->getT()))) {
            res.emplace(*curr);
        }
    }
    return res;
}
