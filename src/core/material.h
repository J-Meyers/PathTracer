
#pragma once

#include "core/spectrum.h"
#include "geometry/ray.h"

class RadianceCalculator;

struct BSSRDF {};
class ISect;

struct MaterialParameters {
  float ior;        // index of refcation
  float cone_angle; // reflection cone angle
  Spectrum diffuse;
  Spectrum emmisive;
  float reflectivity;
};

class Material {
public:
  virtual ~Material() = default;

  // U and V used for stratified sampling to keep rays "randomly" going in the
  // same general direction, this reduces variance
  [[nodiscard]] virtual Spectrum sample(const Ray &ray, const ISect &isect,
                                        const RadianceCalculator &rad_calc,
                                        int depth, double u,
                                        double v) const = 0;

  [[nodiscard]] virtual Spectrum
  emmisivity(const Spectrum &prev_radiance) const = 0;
};

class LambertianMaterial : public Material {
public:
  LambertianMaterial(const MaterialParameters &params) : params(params) {}

  [[nodiscard]] Spectrum sample(const Ray &ray, const ISect &isect,
                                const RadianceCalculator &rad_calc, int depth,
                                double u, double v) const override;

  [[nodiscard]] Spectrum
  emmisivity(const Spectrum &prev_radiance) const override;

private:
  MaterialParameters params;
};

class MaterialInteraction {
  [[nodiscard]] Spectrum sample(const Ray &ray);

  Material *m;
};

class DummyMaterial : public Material {
  [[nodiscard]] Spectrum sample(const Ray &, const ISect &,
                                const RadianceCalculator &, int, double,
                                double) const override {
    return Spectrum(.02);
  }

  [[nodiscard]] Spectrum
  emmisivity(const Spectrum &prev_radiance) const override {
    return prev_radiance;
  }
};