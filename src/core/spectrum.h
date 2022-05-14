#pragma once

#include "geometry/constants.h"
#include <array>
#include <cmath>
#include <cassert>
#include <glm/vec3.hpp>

class SampledSpectrum {
public:
  SampledSpectrum() = default;
  // assumes all instances of SampledSpectrum have the same number of samples
  static constexpr int beginWaveLength = 400;
  static constexpr int endWaveLength = 700;
  static constexpr int numSamples = 60;

  explicit SampledSpectrum(double initVal) : intensity() {
    std::fill(intensity.begin(), intensity.end(), initVal);
  }

  // default copy constructor should be enough w/ vector

  double &operator[](int i) { return intensity[i]; }

  const double &operator[](int i) const { return intensity[i]; }

  SampledSpectrum operator+(const SampledSpectrum &other) const {
    SampledSpectrum out = *this;
    out += other;
    return out;
  }

  SampledSpectrum &operator+=(const SampledSpectrum &other) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] += other[i];
    }
    return *this;
  }

  SampledSpectrum operator-() const {
    SampledSpectrum out = *this;
    for (int i = 0; i < numSamples; ++i) {
      out[i] *= -1;
    }
    return out;
  }

  SampledSpectrum &operator-=(const SampledSpectrum &other) {
    *this += -other;
    return *this;
  }

  SampledSpectrum operator-(const SampledSpectrum &other) const {
    SampledSpectrum out = *this;
    out -= other;
    return out;
  }

  SampledSpectrum &operator*=(double f) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] *= f;
    }
    return *this;
  }

  SampledSpectrum operator*(double f) const {
    SampledSpectrum out = *this;
    out *= f;
    return out;
  }

  SampledSpectrum operator/=(double f) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] /= f;
    }
    return *this;
  }

  SampledSpectrum operator/(double f) const {
    SampledSpectrum out = *this;
    out /= f;
    return out;
  }

  SampledSpectrum &operator*=(const SampledSpectrum &other) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] *= other[i];
    }
    return *this;
  }

  SampledSpectrum operator*(const SampledSpectrum &other) const {
    SampledSpectrum out = *this;
    out *= other;
    return out;
  }

  SampledSpectrum &operator/=(const SampledSpectrum &other) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] /= other[i];
    }
    return *this;
  }

  SampledSpectrum operator/(const SampledSpectrum &other) const {
    SampledSpectrum out = *this;
    out /= other;
    return out;
  }

  // within epsilon
  [[nodiscard]] bool isBlack() const {
    return std::all_of(intensity.begin(), intensity.end(),
                       [](double x) { return x < EPSILON; });
  }

  [[nodiscard]] SampledSpectrum sqrt() const {
    SampledSpectrum out = *this;
    for (int i = 0; i < numSamples; ++i) {
      out[i] = std::sqrt(out[i]);
    }
    return out;
  }

  static SampledSpectrum lerp(const SampledSpectrum &s1,
                              const SampledSpectrum &s2, double t) {
    assert(0 <= t && t <= 1);
    return s1 * (1.0 - t) + s2 * t;
  }

  static SampledSpectrum
  clamp(const SampledSpectrum &s, double l = 0.0,
        double h = std::numeric_limits<double>::infinity()) {
    SampledSpectrum out = s;
    for (int i = 0; i < numSamples; ++i) {
      out[i] = std::clamp(out[i], l, h);
    }
    return out;
  }

  static void initRGBConversion() { makeIntegrators(); }

  [[nodiscard]] glm::dvec3 toRGB() const;

private:
    std::array<double, numSamples>
        intensity; // spans [400 nm, 700 nm] uniformly

  [[nodiscard]] glm::dvec3 toXYZ() const;

  static void makeIntegrators();

  static double average(std::array<int, nCIESamples> wavelength,
                        std::array<double, nCIESamples> weights, int left,
                        int right);
};

extern SampledSpectrum XIntegrator;
extern SampledSpectrum YIntegrator;
extern SampledSpectrum ZIntegrator;

inline glm::dvec3 toRGB(const glm::dvec3 &s) { return s; }
inline glm::dvec3 toRGB(const SampledSpectrum &s) { return s.toRGB(); }

using Spectrum = glm::dvec3;
