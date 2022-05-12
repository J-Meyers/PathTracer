#include "spectrum.h"

#include <iostream>

Spectrum XIntegrator{};
Spectrum YIntegrator{};
Spectrum ZIntegrator{};

void Spectrum::makeIntegrators() {
  int step =
      (endWaveLength - beginWaveLength) / numSamples; // assumes integer step
  for (int i = 0; i < numSamples; ++i) {
    int left = beginWaveLength + i * step;
    int right = beginWaveLength + (i + 1) * step;

    XIntegrator[i] = average(CIE_lambda, CIE_X, left, right);
    YIntegrator[i] = average(CIE_lambda, CIE_Y, left, right);
    ZIntegrator[i] = average(CIE_lambda, CIE_Z, left, right);
  }
}

//numerical integration of the spectrum to convert it to XYZ
//does integration as a linear combination of the sample intensities
//directly copied from the book
glm::dvec3 Spectrum::toXYZ() const {
    glm::dvec3 result(0.0);

    for (int i = 0; i < numSamples; ++i) {
        result[0] += XIntegrator[i] * intensity[i];
        result[1] += YIntegrator[i] * intensity[i];
        result[2] += ZIntegrator[i] * intensity[i];
    }

    return result;
}

//Directly copied magic formula from the book
glm::dvec3 Spectrum::toRGB() const {
  glm::dvec3 xyz = toXYZ();
  glm::dvec3 rgb;

  rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
  rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
  rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];

  if (rgb[0] != 0)
    std::cout << rgb[0] << ' ' << rgb[1] << ' ' << rgb[2] << '\n';

  return rgb;
}

double
Spectrum::average(std::array<int, nCIESamples> wavelength, std::array<double, nCIESamples> weights, int left,
                  int right) {
    //avoid edge cases
    assert(nCIESamples > 1);
    assert(left < right);
    assert(left >= wavelength[0]);
    assert(right <= wavelength[nCIESamples - 1]);


    double sum = 0;
    int i = beginWaveLength - wavelength.front() + left;

    for (int j = 0; j < right - left; ++j) {
        sum += (weights[i + j + 1] + weights[i + j]) * 0.5;
    }

    return sum / (right - left);
}