#pragma once

#include "core/radiance_calculator.h"
#include "geometry/spectrum.h"
#include "scene.h"
#include <glm/vec3.hpp>
#include <memory>

struct RenderResult {
  struct RGB {
    unsigned char r, g, b;

    RGB &operator+=(const RGB &other) {
      r += other.r;
      g += other.g;
      b += other.b;
      return *this;
    };

    RGB &operator/=(int n) {
      r /= n;
      g /= n;
      b /= n;
      return *this;
    };
  };

  RGB &operator()(int x, int y) { return pixels[y * width + x]; }

  int width, height;
  std::vector<RGB> pixels;
};

class Renderer {
public:
  Renderer(const Scene &scene, int width, int height)
      : scene_(scene), width_(width), height_(height), rad_calc_(scene_) {}

  RenderResult renderScene();

  Spectrum tracePixel(int i, int j);

private:
  const Scene &scene_;
  int width_;
  int height_;
  int samples_per_pixel_ = 20;
  const RadianceCalculator rad_calc_;
};
