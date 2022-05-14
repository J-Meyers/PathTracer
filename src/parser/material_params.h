
#pragma once

#include "geometry/spectrum.h"

struct MaterialParameters {
  double ior;        // index of refraction
  double cone_angle; // reflection cone angle
  Spectrum diffuse;
  Spectrum emissive;
  double reflectivity;
};
