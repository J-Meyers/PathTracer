
#pragma once

#include "spectrum.h"
#include "geometry/ray.h"

struct BSSRDF {
};

class Material {
    virtual ~Material() = default;

    [[nodiscard]] virtual Spectrum sample(const Ray &ray) const = 0;
};

class MaterialInteraction {
    [[nodiscard]] Spectrum sample(const Ray &ray);

    Material *m;
};