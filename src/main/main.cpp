//
// Created by julian on 5/7/22.
//
#include <iostream>
#include "core/camera.h"
#include <glm/vec3.hpp>

int main() {
  Camera c{{0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 100, 50, .436};
  std::cout << "Test1\n";
}