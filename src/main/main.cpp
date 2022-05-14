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
  Camera camera(eye, look, up, h, w, toRads(vertical_fov), .01,
                std::sqrt(10.0));

  SceneBuilder sb(camera);
  DirRelativeOpener opener("../../scenes");
  auto in = opener.open("CornellBox-Original.obj");
  loadObjFile(*in, opener, sb);

  Renderer r(sb.scene(), w, h);
  return r.renderScene();
}

RenderResult renderSphereCornell(int w, int h) {
  glm::dvec3 eye(0, 1, 3);
  glm::dvec3 up(0, 1, 0);
  glm::dvec3 lookat(0, 1, 0);
  glm::dvec3 look = glm::normalize(lookat - eye);
  double vertical_fov = 50.0;
  // Short .5, long 4
  Camera camera(eye, look, up, h, w, toRads(vertical_fov), .01, 4);

  SceneBuilder sb(camera);
  DirRelativeOpener opener("../../scenes");
  auto in = opener.open("CornellBox-Original.obj");
  loadObjFile(*in, opener, sb);

  // Added Sphere
  MaterialParameters special_sphere_params{3, .001, {.999, .999, .999}, {}, 0};
  sb.addSphere(glm::dvec3{-.38, .281, .38}, .28, special_sphere_params);
  sb.setEnvironmentColour({0.0725, 0.071, 0.068});

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

  // Add light sources
  auto light_params = MaterialParameters{1.0, 0.0, {}, glm::dvec3{4}, -1};
  sb.addSphere(glm::dvec3{.5, 1, 3}, 1, light_params);
  sb.addSphere(glm::dvec3{1, 1, 3}, 1, light_params);

  Renderer r(sb.scene(), w, h);
  return r.renderScene();
}

RenderResult renderCe(int w, int h) {
  glm::dvec3 eye(.27, 1.15, .36);
  glm::dvec3 up(0, 0, -1);
  glm::dvec3 lookat{0};
  glm::dvec3 look = glm::normalize(lookat - eye);
  double vertical_fov = 40.0;
  Camera camera(eye, look, up, h, w, toRads(vertical_fov), .01, .845);

  SceneBuilder sb(camera);
  DirRelativeOpener opener("../../scenes");
  auto in = opener.open("ce.obj");
  loadObjFile(*in, opener, sb);

  // Add light sources
  auto light_params = MaterialParameters{1.0, 0.0, {}, {10, 10, 10}, -1};
  sb.addSphere(glm::dvec3{0, 1.6, 0}, 1, light_params);

  auto other_light_params =
      MaterialParameters{1.0, 0.0, {}, glm::dvec3(2.27, 3, 2.97) * 0.25, -1};
  sb.addSphere(glm::dvec3{-.2, 5.9, -.3}, 5, other_light_params);

  auto final_params = MaterialParameters{1.0, 0.0, {.2, .2, .2}, {}, -1};
  sb.addSphere(glm::dvec3{0, 0, 0}, 10, final_params);

  Renderer r(sb.scene(), w, h);
  return r.renderScene();
}

int main() {
  if constexpr (std::is_same_v<SampledSpectrum, Spectrum>) {
    SampledSpectrum::initRGBConversion();
  }

  int w = 512;
  int h = 512;
  auto img = renderSphereCornell(w, h);

  FILE *f = fopen("../../image.ppm", "w"); // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (auto c : img.pixels)
    fprintf(f, "%d %d %d ", c.r, c.g, c.b);
}
