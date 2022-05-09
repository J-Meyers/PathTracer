#pragma once

#include "scene.h"
#include <glm/vec3.hpp>
#include "spectrum.h"
#include <memory>

struct RenderResult {
    struct RGB {
        unsigned char r, g, b;

        RGB &operator+=(const RGB &other) {
            r += other.r;
            g += other.g;
            b += other.b;
            return *this;
        };

        RGB &operator/=(int n) {
            r /= n;
            g /= n;
            b /= n;
            return *this;
        };
    };

    RGB &operator()(int x, int y) {
        return pixels[y * width + x];
    }

    int width, height;
    std::vector<RGB> pixels;
};

class Renderer {
public:
    Renderer(std::unique_ptr<Scene> scene, int width, int height) : scene_(std::move(scene)), width_(width),
                                                                    height_(height) {}

    RenderResult renderScene();

    RenderResult::RGB tracePixel(int i, int j);

    Spectrum tracePath(Ray &ray, int depth);

private:
    std::unique_ptr<Scene> scene_;
    int width_;
    int height_;
    int samples_per_pixel_ = 1;
    int max_depth_ = 6;
};
