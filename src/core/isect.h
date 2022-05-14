
#pragma once

class Material;
class SceneObject;

#include "spectrum.h"
#include <glm/vec3.hpp>
#include <memory>

class ISect {
public:
  [[nodiscard]] glm::dvec3 getN() const { return face_normal_; }

  [[nodiscard]] double getT() const { return t_; }

  [[nodiscard]] glm::dvec3 getPt() const { return pt_; }

  [[nodiscard]] const Material &getMat() const { return *mat_; }

  void setPt(const glm::dvec3 &pt) { pt_ = pt; }

  void setN(glm::dvec3 face_normal) { face_normal_ = face_normal; }

  void setT(double t) { t_ = t; }

  void setMat(Material *m) { mat_ = m; }

  void setObj(SceneObject *o) { obj_ = o; }

private:
  glm::dvec3 pt_;
  glm::dvec3 face_normal_;
  double t_;
  Material *mat_;
  SceneObject *obj_;
};
