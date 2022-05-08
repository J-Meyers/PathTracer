#pragma once

#include "geometry/constants.h"
#include <array>
#include <cmath>
#include <cassert>
#include <glm/vec3.hpp>

class Spectrum {
public:
    // assumes all instances of Spectrum have the same number of samples
    static constexpr int beginWaveLength = 400;
    static constexpr int endWaveLength = 700;
    static constexpr int numSamples = 60;

    Spectrum(double initVal) : intensity() {
        std::fill(intensity.begin(), intensity.end(), initVal);
    }

    // default copy constructor should be enough w/ vector

    double &operator[](int i) { return intensity[i]; }

    const double &operator[](int i) const { return intensity[i]; }

    Spectrum operator+(const Spectrum &other) const {
        Spectrum out = *this;
        out += other;
        return out;
    }

    Spectrum &operator+=(const Spectrum &other) {
        for (int i = 0; i < numSamples; ++i) {
            intensity[i] += other[i];
        }
        return *this;
    }

    Spectrum operator-() const {
        Spectrum out = *this;
        for (int i = 0; i < numSamples; ++i) {
            out[i] *= -1;
        }
        return out;
    }

    Spectrum &operator-=(const Spectrum &other) {
        *this += -other;
        return *this;
    }

    Spectrum operator-(const Spectrum &other) const {
        Spectrum out = *this;
        out -= other;
        return out;
    }

    Spectrum &operator*=(const Spectrum &other) {
        for (int i = 0; i < numSamples; ++i) {
            intensity[i] *= other[i];
        }
        return *this;
    }

    Spectrum operator*(const Spectrum &other) const {
        Spectrum out = *this;
        out *= other;
        return out;
    }

    Spectrum &operator/=(const Spectrum &other) {
        for (int i = 0; i < numSamples; ++i) {
            intensity[i] /= other[i];
        }
        return *this;
    }

    Spectrum operator/(const Spectrum &other) const {
        Spectrum out = *this;
        out /= other;
        return out;
    }

    //within epsilon
    [[nodiscard]] bool isBlack() const {
        return std::all_of(intensity.begin(), intensity.end(), [](double x) {
            return x < EPSILON;
        });
    }

    [[nodiscard]] Spectrum sqrt() const {
        Spectrum out = *this;
        for (int i = 0; i < numSamples; ++i) {
            out[i] = std::sqrt(out[i]);
        }
        return out;
    }

    static Spectrum lerp(const Spectrum &s1, const Spectrum &s2, double t) {
        assert(0 <= t && t <= 1);
        return s1 * (1.0 - t) + s2 * t;
    }

    static Spectrum clamp(const Spectrum &s, double l = 0.0, double h = std::numeric_limits<double>::infinity()) {
        Spectrum out = s;
        for (int i = 0; i < numSamples; ++i) {
            out[i] = std::clamp(out[i], l, h);
        }
        return out;
    }

    static void initRGBConversion() {
        makeIntegrators();
    }

    glm::dvec3 toRGB() const;

private:
    std::array<double, numSamples> intensity; // spans [400 nm, 700 nm] uniformly

    glm::dvec3 toXYZ() const;

    //turn integration of spectrum in to linear combination of samples
    static Spectrum XIntegrator;
    static Spectrum YIntegrator;
    static Spectrum ZIntegrator;

    static void makeIntegrators();

    static double average(std::array<int, nCIESamples> wavelength, std::array<double, nCIESamples> weights, int left,
                          int right);
};

