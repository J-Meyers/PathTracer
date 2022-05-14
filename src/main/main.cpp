#include "core/camera.h"
#include "core/renderer.h"
#include "core/scene.h"
#include "core/scene_builder.h"
#include "core/sphere.h"
#include "core/trimesh.h"
#include "parser/parser.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <memory>

double toRads(double degs) { return degs * M_PI / 180.0; }

RenderResult renderCornell(int w, int h) {
  glm::dvec3 eye(0, 1, 3);
  glm::dvec3 up(0, 1, 0);
  glm::dvec3 lookat(0, 1, 0);
  glm::dvec3 look = glm::normalize(lookat - eye);
  double vertical_fov = 50.0;
  Camera camera(eye, look, up, h, w, toRads(vertical_fov), .1, std::sqrt(10.0));

  SceneBuilder sb(camera);
  DirRelativeOpener opener("../../scenes");
  auto in = opener.open("CornellBox-Original.obj");
  loadObjFile(*in, opener, sb);

  Renderer r(sb.scene(), w, h);
  return r.renderScene();
}

RenderResult renderSuzanne(int w, int h) {
  glm::dvec3 eye(1, -.45, 4);
  glm::dvec3 up(0, 1, 0);
  glm::dvec3 lookat(1, -.6, .4);
  glm::dvec3 look = glm::normalize(lookat - eye);
  double vertical_fov = 40.0;
  Camera camera(eye, look, up, h, w, toRads(vertical_fov), .01, .845);

  SceneBuilder sb(camera);
  DirRelativeOpener opener("../../scenes");
  auto in = opener.open("suzanne.obj");
  loadObjFile(*in, opener, sb);

  Renderer r(sb.scene(), w, h);
  return r.renderScene();
}

int main() {
  if constexpr (std::is_same_v<SampledSpectrum, Spectrum>) {
    SampledSpectrum::initRGBConversion();
  }

  int w = 100;
  int h = 100;
  auto img = renderCornell(w, h);

  FILE *f = fopen("../../image.ppm", "w"); // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (auto c : img.pixels)
    fprintf(f, "%d %d %d ", c.r, c.g, c.b);
}
