
#pragma once

#include "material.h"
#include "scene_object.h"
#include "spectrum.h"
#include <glm/vec3.hpp>
#include <memory>

class ISect {
public:
  [[nodiscard]] glm::dvec3 getN() const { return face_normal_; }

  [[nodiscard]] double getT() const { return t_; }

  void setN(glm::dvec3 face_normal) { face_normal_ = face_normal; }

  void setT(double t) { t_ = t; }

  void setMat(Material *m) { mat_ = m; }

  void setObj(SceneObject *o) { obj_ = o; }

  void setSpectrum(const Spectrum &s) { spectrum_ = s; }

  [[nodiscard]] Spectrum getSpectrum() const { return spectrum_; }

private:
  glm::dvec3 face_normal_;
  double t_;
  Material *mat_;
  SceneObject *obj_;
  Spectrum spectrum_;
};
