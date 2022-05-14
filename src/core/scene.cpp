#include "scene.h"
#include <numeric>

void Scene::add(std::unique_ptr<Geometry> geometry) {
  geometry->computeBoundingBox();
  objects_.push_back(std::move(geometry));
}

std::optional<ISect> Scene::intersect(const Ray &ray) const {
  std::optional<ISect> res;
  for (const auto &object : objects_) {
    if (auto curr = object->intersect(ray);
        curr && (!res || (curr->getT() < res->getT()))) {
      res.emplace(*curr);
    }
  }
  return res;
}
Spectrum Scene::backgroundRadiance(const Ray &) const {
  return background_radiance_;
}
