#include "core/camera.h"
#include "core/renderer.h"
#include "core/scene.h"
#include "core/sphere.h"
#include "core/trimesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <memory>

float toRads(float degs) { return degs * M_PI / 180.0; }

int main() {
  if constexpr (std::is_same_v<SampledSpectrum, Spectrum>) {
    SampledSpectrum::initRGBConversion();
  }

  int w = 100;
  int h = 100;
  Camera cam{{0, 0, 3}, {0, 0, -1}, {0, 1, 0}, h, w, 0.872665};
  Scene scene(cam);
  //  scene.setBackgroundRadiance(Spectrum{0.725, .71, .68} * .1);
  scene.setBackgroundRadiance(Spectrum{0});
  MaterialParameters simple_params{1.0, toRads(5.), Spectrum{.999}, Spectrum{1},
                                   .95};
  LambertianMaterial simple_mat{simple_params};

  glm::dvec3 tri[3];
  tri[0] = {-1, 0, 0};
  tri[1] = {0, 1, 0};
  tri[2] = {1, 0, 0};
  DummyMaterial dumb_mat;
  //  auto triangle = std::make_unique<Triangle>(&scene, &dumb_mat, tri);
  //  scene.add(std::move(triangle));

  //  auto sphere = std::make_unique<Sphere>(&scene, &simple_mat);
  //  auto transform_mat = glm::translate(glm::mat4(1.0f), glm::vec3{-.28, .281,
  //  .38}); transform_mat /= .28; auto kid =
  //  scene.root_.createChild(transform_mat);
  //  sphere->setTransform(&scene.root_);
  //  scene.add(std::move(sphere));

  Renderer r(scene, w, h);
  RenderResult img = r.renderScene();

  FILE *f = fopen("image.ppm", "w"); // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (auto c : img.pixels)
    fprintf(f, "%d %d %d ", c.r, c.g, c.b);
}
