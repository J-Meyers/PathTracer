
#pragma once

#include <glm/vec3.hpp>

class ISect {
public:

    [[nodiscard]] glm::dvec3 getN() const { return face_normal_; }

    [[nodiscard]] double getT() const { return t_; }

    void setN(glm::dvec3 face_normal) {
        face_normal_ = face_normal;
    }

    void setT(double t) {
        t_ = t;
    }

private:
    glm::dvec3 face_normal_;
    double t_;

};
