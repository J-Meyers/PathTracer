
#pragma once

#include "geometry/ray.h"
#include "spectrum.h"

struct BSSRDF {};

class Material {
public:
  virtual ~Material() = default;

  [[nodiscard]] virtual Spectrum sample(const Ray &ray) const = 0;
};

class MaterialInteraction {
  [[nodiscard]] Spectrum sample(const Ray &ray);

  Material *m;
};

class DummyMaterial : public Material {
  [[nodiscard]] Spectrum sample(const Ray &) const override {
    return Spectrum(1.0);
  }
};