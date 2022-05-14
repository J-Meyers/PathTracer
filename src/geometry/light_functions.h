#pragma once
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <random>

namespace light_functions {
extern std::mt19937 rng;

inline double random_uniform() {
  std::uniform_real_distribution<> dist(0.0, 1.0);
  return dist(rng);
}

// return reflection angle given incident direction and normal
inline glm::dvec3 reflect(const glm::dvec3 &n, const glm::dvec3 &in) {
  double cosIn = -1 * glm::dot(n, in);
  return 2.0 * cosIn * n + in;
}

// return refraction direction given normal dir, incident direction, and indices
// n1 corresponds to medium being exited, n2 is medium being entered
// returns 0,0,0 in the case of total internal reflection
inline glm::dvec3 refract(const glm::dvec3 &n, const glm::dvec3 &in, double n1,
                          double n2) {
  double ratio = n1 / n2;
  double cosIn = -1 * glm::dot(n, in);
  double sinOut = ratio * ratio * (1.0 - cosIn * cosIn);

  // total internal reflection
  if (sinOut > 1.0) {
    return glm::dvec3(1.0);
  }

  double cosOut = sqrt(1.0 - sinOut);
  return ratio * in + (n * cosIn - cosOut) * n;
}

// return the reflectance give normal direction, incident direction, and indices
// n1 corresponds to medium being exited, n2 is medium being entered
inline double reflectance(const glm::dvec3 &n, const glm::dvec3 &in, double n1,
                          double n2) {
  double ratio = n1 / n2;
  double cosIn = -1 * glm::dot(n, in);
  double sinOut = ratio * ratio * (1 - cosIn * cosIn);

  // check for total internal reflection
  if (sinOut > 1.0) {
    return 1.0;
  }

  // return average of reflectances from both polarizations
  double cosOut = std::sqrt(1 - sinOut);
  double rOrthogonal = (n1 * cosIn - n2 * cosOut) / (n1 * cosIn + n2 * cosOut);
  double rParallel = (n2 * cosIn - n1 * cosOut) / (n2 * cosIn + n1 * cosOut);
  return (rOrthogonal * rOrthogonal + rParallel + rParallel) / 2.0;
}

// given uniformly random u,v coordinates in [0, 1] x [0, 1]
// uniformly samples a disk centered at the origin and with radius 1
inline glm::dvec2 sampleUnitDisk(double u, double v) {
  // convert to the space [-1, 1] x [-1, 1]
  double squareX = 2.0 * u - 1.0;
  double squareY = 2.0 * v - 1.0;

  // special case of origin
  if (squareX == 0.0 && squareY == 0.0) {
    return glm::dvec2(0.0);
  }

  double theta;
  double r;

  if (std::abs(squareX) > std::abs(squareY)) {
    r = squareX;
    theta = M_PI_4 * (squareY / squareX);
  } else {
    r = squareY;
    theta = M_PI_2 - M_PI_4 * (squareX / squareY);
  }

  return r * glm::dvec2(std::cos(theta), std::sin(theta));
}

// given uniformly random u,v coordinates in [0,1] x [0,1]
// randomly samples points on the unit hemisphere with cosine weighting
// uses Malley's method of sampling a disk and extrapolating to the sphere
inline glm::dvec3 sampleCosineHemisphere(double u, double v) {
  glm::dvec2 diskSample = sampleUnitDisk(u, v);
  double z =
      std::sqrt(1 - diskSample.x * diskSample.x - diskSample.y * diskSample.y);
  return {diskSample.x, diskSample.y, std::max(z, 0.0)};
}

// given uniformly random u,v coordinates in [0,1] x [0,1]
// uniformly samples the cone about the positive z axis with a given solid angle
// takes cosTheta to avoid expensive trig re-computation
inline glm::dvec3 sampleCone(double u, double v, double cosThetaMax) {
  double cosTheta = (1 - u) + u * cosThetaMax;
  double sinTheta = std::sqrt(1 - cosTheta * cosTheta);
  double phi = v * 2 * M_PI;
  return {std::cos(phi) * sinTheta, std::sin(phi) * sinTheta, cosTheta};
}
}; // namespace light_functions
