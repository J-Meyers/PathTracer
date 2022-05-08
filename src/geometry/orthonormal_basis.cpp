#include "orthonormal_basis.h"

#include "constants.h"

namespace OrthonormalBasis {
    glm::dmat3 fromZY(const glm::dvec3 &z, const glm::dvec3 &y) {
        auto x = glm::normalize(glm::cross(y, z));
        auto new_y = glm::normalize(glm::cross(z, x)); //ensure perpendicular
        return glm::dmat3(x, new_y, glm::normalize(z));
    }

    glm::dmat3 fromZ(const glm::dvec3 &z) {
        auto temp_y = std::abs(glm::dot(z, glm::dvec3{1, 0, 0})) > (1.0 - EPSILON)
                      ? glm::dvec3{0, 1, 0}
                      : glm::dvec3{1, 0, 0};
        auto x = glm::normalize(glm::cross(temp_y, z));
        auto y = glm::normalize(glm::cross(z, x));
        return glm::dmat3(x, y, glm::normalize(z));
    }
} // namespace OrthonormalBasis
