#include "scene_builder.h"
#include "material.h"
#include "sphere.h"
#include "trimesh.h"

void SceneBuilder::addSphere(const glm::dvec3 &pos, double radius,
                             const MaterialParameters &material) {
  auto s = std::make_unique<Sphere>(&scene_, fromParams(material), pos, radius);
  scene_.add(std::move(s));
}

void SceneBuilder::addTriangle(const glm::dvec3 &v0, const glm::dvec3 &v1,
                               const glm::dvec3 &v2,
                               const MaterialParameters &material) {
  glm::dvec3 vertArr[3] = {v0, v1, v2};
  auto t = std::make_unique<Triangle>(&scene_, fromParams(material), vertArr);
  scene_.add(std::move(t));
}

void SceneBuilder::setEnvironmentColour(const glm::dvec3 &c) {
  scene_.setBackgroundRadiance(c);
}
