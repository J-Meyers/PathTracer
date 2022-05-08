
#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

// Homogenous transformation of vec3
inline glm::dvec3 operator*(const glm::dmat4x4 &mat, const glm::dvec3 &vec) {
  glm::dvec4 vec4(vec[0], vec[1], vec[2], 1.0);
  auto ret = mat * vec4;
  // TODO: Check if this change screws stuff up
  return glm::dvec3(ret[0], ret[1], ret[2]) / ret[3];
}

class TransformNode {
public:
  TransformNode &createChild(const glm::dmat4 &transform) {
    // Can't use make_unique because of protected constructor
    std::unique_ptr<TransformNode> child(new TransformNode(this, transform));
    children_.push_back(std::move(child));
    return *children_.back().get();
  }

  glm::dvec3 globalToLocal(const glm::dvec3 &global) const {
    return inverse_ * global;
  }

  glm::dvec3 localToGlobal(const glm::dvec3 &local) const {
    return transform_ * local;
  }

  glm::dvec4 localToGlobal(const glm::dvec4 &local) const {
    return transform_ * local;
  }

  glm::dvec3 localToGlobalNormal(const glm::dvec3 &local) const {
    return glm::normalize(normal_inverse_ * local);
  }

  const glm::dmat4 &getTransform() const { return transform_; }

protected:
  TransformNode(TransformNode *parent, const glm::dmat4 &transform)
      : parent_(parent),
        transform_(parent == nullptr ? transform
                                     : parent->transform_ * transform),
        inverse_(glm::inverse(transform_)),
        normal_inverse_(
            glm::transpose(glm::inverse(glm::dmat3x3(transform_)))) {}

  TransformNode *parent_;
  std::vector<std::unique_ptr<TransformNode>> children_{};
  glm::dmat4 transform_;
  glm::dmat4 inverse_;
  glm::dmat3 normal_inverse_;
};

class TransformNodeRoot : public TransformNode {
public:
  TransformNodeRoot() : TransformNode(nullptr, glm::dmat4(1.0)) {}
};
