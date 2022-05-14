
#include "core/material.h"
#include "core/isect.h"
#include "geometry/light_functions.h"
#include "geometry/orthonormal_basis.h"

#include "core/radiance_calculator.h"

using namespace light_functions;

Spectrum LambertianMaterial::sample(const Ray &ray, const ISect &isect,
                                    const RadianceCalculator &rad_calc,
                                    int depth, double u, double v) const {
  float n1 = 1.0f;
  float n2 = params.ior;
  glm::dvec3 n = isect.getN();
  // TODO: check the correct direction of this
  if (glm::dot(n, ray.getDir()) > 0.0) {
    n *= -1;
    std::swap(n1, n2);
  }

  auto my_reflectance = reflectance(n, ray.getDir(), n1, n2);

  // TODO: consider jittering point away from surface

  // randomly reflect based on reflectance
  if (random_uniform() < my_reflectance) {
    glm::dvec3 r = reflect(n, ray.getDir());
    r = OrthonormalBasis::fromZ(r) *
        sampleCone(u, v, std::cos(params.cone_angle));
    return rad_calc.radiance(Ray(isect.getPt() + n * EPSILON, r), depth + 1);
  }
  Ray outgoing{isect.getPt() + n * EPSILON,
               OrthonormalBasis::fromZ(n) * sampleCosineHemisphere(u, v)};
  return params.diffuse * rad_calc.radiance(outgoing, depth + 1);
}
Spectrum LambertianMaterial::emissivity(const Spectrum &prev_radiance) const {
  return params.emissive + prev_radiance;
}
Spectrum ReflectiveMaterial::sample(const Ray &ray, const ISect &isect,
                                    const RadianceCalculator &rad_calc,
                                    int depth, double u, double v) const {
  glm::dvec3 n = isect.getN();
  // TODO: check the correct direction of this
  if (glm::dot(n, ray.getDir()) > 0.0) {
    n *= -1;
  }

  // randomly reflect based on reflectance
  if (random_uniform() < params.reflectivity) {
    glm::dvec3 r = reflect(n, ray.getDir());
    // Sample randomly
    r = OrthonormalBasis::fromZ(r) *
        sampleCone(u, v, std::cos(params.cone_angle));
    return rad_calc.radiance(Ray(isect.getPt() + n * EPSILON, r), depth + 1);
  }
  Ray outgoing{isect.getPt() + n * EPSILON,
               OrthonormalBasis::fromZ(n) * sampleCosineHemisphere(u, v)};
  return params.diffuse * rad_calc.radiance(outgoing, depth + 1);
}
Spectrum ReflectiveMaterial::emissivity(const Spectrum &prev_radiance) const {
  return params.emissive + prev_radiance;
}

std::unique_ptr<Material> fromParams(const MaterialParameters &p) {
  if (p.reflectivity < EPSILON) {
    return std::make_unique<LambertianMaterial>(p);
  }
  return std::make_unique<ReflectiveMaterial>(p);
}
