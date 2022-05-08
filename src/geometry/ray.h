#pragma once

#include <glm/vec3.hpp>

class Ray {
public:
    constexpr Ray(const glm::vec3 &pos, const glm::vec3 &dir)
            : pos_(pos), dir_(dir) {}

    [[nodiscard]] constexpr glm::vec3 getPos() const { return pos_; }

    [[nodiscard]] constexpr glm::vec3 getDir() const { return dir_; }

    void setPos(const glm::vec3 &pos) { pos_ = pos; }

    void setDir(const glm::vec3 &dir) { dir_ = dir; }

    [[nodiscard]] constexpr glm::vec3 operator()(float t) const {
        return pos_ + t * dir_;
    }

private:
    glm::vec3 pos_;
    glm::vec3 dir_;
};