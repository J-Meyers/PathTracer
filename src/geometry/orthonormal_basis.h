#pragma once

#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

namespace OrthonormalBasis {
glm::dmat3 fromZ(const glm::dvec3 &z);
glm::dmat3 fromZY(const glm::dvec3 &z, const glm::dvec3 &y);
} // namespace OrthonormalBasis