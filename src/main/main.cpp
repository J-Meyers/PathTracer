#include "core/camera.h"
#include "core/renderer.h"
#include "core/scene.h"
#include "core/sphere.h"
#include <glm/vec3.hpp>
#include <iostream>
#include <memory>

int main() {
  Spectrum::initRGBConversion();
  int w = 100;
  int h = 100;
  Camera cam{{0, 0, 5}, {0, 0, -1}, {0, 1, 0}, h, w, .436};
  Scene scene(cam);
  DummyMaterial m;
  auto sphere = std::make_unique<Sphere>(&scene, &m);
  sphere->setTransform(&scene.root_);
  scene.add(std::move(sphere));

  Renderer r(scene, w, h);
  RenderResult img = r.renderScene();

  FILE *f = fopen("image.ppm", "w"); // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (auto c : img.pixels)
    fprintf(f, "%d %d %d ", c.r, c.g, c.b);
}
