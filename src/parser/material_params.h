
#pragma once

#include "geometry/spectrum.h"

struct MaterialParameters {
  float ior;        // index of refraction
  float cone_angle; // reflection cone angle
  Spectrum diffuse;
  Spectrum emissive;
  float reflectivity;
};
