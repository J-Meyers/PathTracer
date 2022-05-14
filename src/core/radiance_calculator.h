
#pragma once

class Scene;

#include "core/spectrum.h"
#include "geometry/ray.h"

class RadianceCalculator {
public:
  RadianceCalculator(const Scene &scene);

  [[nodiscard]] virtual Spectrum radiance(const Ray &ray, int depth) const;

private:
  const Scene &scene_;
  const int max_depth_ = 5;
  const int first_n_samples_ = 1;
  const int n_samples_per_ = 4;
};