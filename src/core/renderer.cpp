
#include "renderer.h"
#include <iostream>

constexpr float gamma_ = 2.2f;

unsigned char fltToCh(double f) {
  return static_cast<unsigned char>(
      std::lround(std::pow(f, 1. / gamma_) * 255));
}
// unsigned char fltToCh(double f) { return static_cast<unsigned char>(f *
// 255.); }
RenderResult::RGB SpectrumToRGB(const Spectrum &s) {
  auto rgb_f = glm::clamp(toRGB(s), 0.0, 1.0);
  return {fltToCh(rgb_f.x), fltToCh(rgb_f.y), fltToCh(rgb_f.z)};
}

RenderResult Renderer::renderScene() {
  RenderResult res{width_, height_, {}};
  res.pixels.resize(width_ * height_);
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      Spectrum sum;
      for (int k = 0; k < samples_per_pixel_; k++) {
        sum += tracePixel(i, j);
      }
      sum /= samples_per_pixel_;
      res(i, j) = SpectrumToRGB(sum);
    }
  }
  return res;
}

Spectrum Renderer::tracePixel(int i, int j) {
  auto r = scene_.getCamera().rayThroughPixel(i, j);
  return rad_calc_.radiance(r, 0);
}
