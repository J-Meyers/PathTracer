
#include "core/radiance_calculator.h"
#include "core/scene.h"
#include "geometry/light_functions.h"
#include <cmath>

#include <iostream>

using light_functions::random_uniform;

RadianceCalculator::RadianceCalculator(const Scene &scene) : scene_(scene) {}

Spectrum RadianceCalculator::radiance(const Ray &ray, int depth) const {
  if (depth > max_depth_) {
    return Spectrum(0.f);
  }

  if (++num_rays_cast_ % 100'000 == 0) {
    std::cout << "Rays cast: " << num_rays_cast_ << '\n';
  }

  auto n_samples = depth < first_n_samples_ ? n_samples_per_ : 1;

  auto isect = scene_.intersect(ray);
  if (!isect) {
    return scene_.backgroundRadiance(ray);
  }

  auto &mat = isect->getMat();

  Spectrum res{0};
  for (auto i = 0; i < n_samples; ++i) {
    for (auto j = 0; j < n_samples; ++j) {
      auto u = (i + random_uniform()) / n_samples;
      auto v = (j + random_uniform()) / n_samples;
      res += mat.sample(ray, isect.value(), *this, depth, u, v);
    }
  }
  auto avg_pre_addition = res / (std::pow(n_samples, 2));
  auto result = mat.emissivity(avg_pre_addition);
  return result;
}
