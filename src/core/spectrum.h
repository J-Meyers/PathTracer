#pragma once
#include "geometry/epsilon.h"
#include <vector>
#include <cmath>
#define SPECTRUM_SIZE (60)

class Spectrum {
public:
  // assumes all instances of Spectrum have the same number of samples
  static const int numSamples = SPECTRUM_SIZE;

  Spectrum(double initVal) : intensity(SPECTRUM_SIZE, initVal) {}

  // default copy constructor should be enough w/ vector

  double &operator[](int i) { return intensity[i]; }

  const double &operator[](int i) const { return intensity[i]; }

  Spectrum operator+(const Spectrum &other) const {
    Spectrum out = *this;
    out += other;
    return out;
  }

  Spectrum &operator+=(const Spectrum &other) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] += other[i];
    }
    return *this;
  }

  Spectrum operator-() const {
    Spectrum out = *this;
    for (int i = 0; i < numSamples; ++i) {
      out[i] *= -1;
    }
    return out;
  }

  Spectrum &operator-=(const Spectrum &other) {
    *this += -other;
    return *this;
  }

  Spectrum operator-(const Spectrum &other) const {
    Spectrum out = *this;
    out -= other;
    return out;
  }

  Spectrum& operator*=(const Spectrum &other) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] *= other[i];
    }
    return *this;
  }

  Spectrum operator*(const Spectrum &other) const {
    Spectrum out = *this;
    out *= other;
    return out;
  }

  Spectrum &operator/=(const Spectrum &other) {
    for (int i = 0; i < numSamples; ++i) {
      intensity[i] /= other[i];
    }
    return *this;
  }

  Spectrum operator/(const Spectrum &other) const {
    Spectrum out = *this;
    out /= other;
    return out;
  }

  //within epsilon
  bool isBlack() const {
    for (int i = 0; i < numSamples; ++i) {
      if(std::abs(intensity[i]) > EPSILON){
        return false;
      }
    }

    return true;
  }

  Spectrum sqrt() const{
    Spectrum out = *this;
    for(int i = 0; i < numSamples; ++i){
      out[i] = std::sqrt(out[i]);
    }

    return out;
  }

  //Unchecked precondition: 0 <= t <= 1, otherwise extrapolates
  static Spectrum lerp(const Spectrum& s1, const Spectrum& s2, double t){
    return s1 * (1.0 - t) + s2 * t;
  }

  static Spectrum clamp(const Spectrum& s, double l = 0.0, double h = std::numeric_limits<double>::infinity()){
    Spectrum out = s;
    for(int i = 0; i < numSamples; ++i){
      out[i] = std::clamp(out[i], l, h);
    }

    return out;
  }

private:
  std::vector<double> intensity; // spans [400 nm, 700 nm] uniformly
};
