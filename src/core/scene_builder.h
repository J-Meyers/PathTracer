#pragma once

#include "parser/material_params.h"
#include "scene.h"

/*
 * Interface copied almost directly from Path Tracer 3 Ways
 * Implementation details are our own work
 */

class SceneBuilder {
  Scene scene_;

public:
  void addTriangle(const glm::dvec3 &v0, const glm::dvec3 &v1,
                   const glm::dvec3 &v2, const MaterialParameters &material);

  void addSphere(const glm::dvec3 &pos, double radius,
                 const MaterialParameters &material);

  void setEnvironmentColour(const glm::dvec3 &colour);

  [[nodiscard]] const Scene &scene() const { return scene_; }
};
