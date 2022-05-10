
#include "renderer.h"

RenderResult Renderer::renderScene() {
    RenderResult res{width_, height_, {}};
    res.pixels.resize(width_ * height_);
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            RenderResult::RGB sum{0, 0, 0};
            for (int k = 0; k < samples_per_pixel_; k++) {
                sum += tracePixel(i, j);
            }
            sum /= samples_per_pixel_;
            res(i, j) = sum;
        }
    }
    return res;
}

RenderResult::RGB Renderer::tracePixel(int i, int j) {
  auto r = scene_.getCamera().rayThroughPixel(i, j);
  auto s = tracePath(r, max_depth_);
  auto rgb_f = glm::clamp(s.toRGB(), 0.0, 1.0);
    // Convert from float to unsigned char
    return {static_cast<unsigned char>(rgb_f.x * 255), static_cast<unsigned char>(rgb_f.y * 255),
            static_cast<unsigned char>(rgb_f.z * 255)};
}

Spectrum Renderer::tracePath(Ray &ray, int depth) {
  if (depth == 0) {
    return Spectrum(0.0);
  }
  if (auto i = scene_.intersect(ray); i.has_value()) {
    return i->getSpectrum();
  }
  return Spectrum(0.0);
}
