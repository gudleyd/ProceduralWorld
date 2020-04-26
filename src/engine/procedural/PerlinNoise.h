//
// Created by lebedev-ivan on 26.04.2020.
//

#pragma once

#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

namespace gdl {

    class PerlinNoise {
    public:
        explicit PerlinNoise(unsigned int seed) {
            this->perms.resize(512);
            std::iota(this->perms.begin(), this->perms.end(), 0);

            std::default_random_engine engine(seed);

            std::shuffle(this->perms.begin(), this->perms.end(), engine);

            this->perms.insert(this->perms.end(), this->perms.begin(), this->perms.end());
        }

        double noise(double x, double y, double z) {
            unsigned int X = (unsigned int)floor(x) & 255u;
            unsigned int Y = (unsigned int)floor(y) & 255u;
            unsigned int Z = (unsigned int)floor(z) & 255u;

            x -= floor(x);
            y -= floor(y);
            z -= floor(z);

            double u = fade(x);
            double v = fade(y);
            double w = fade(z);

            unsigned int A = this->perms[X] + Y;
            unsigned int AA = this->perms[A] + Z;
            unsigned int AB = this->perms[A + 1] + Z;
            unsigned int B = this->perms[X + 1] + Y;
            unsigned int BA = this->perms[B] + Z;
            unsigned int BB = this->perms[B + 1] + Z;

            double res = lerp(w, lerp(v, lerp(u, grad(this->perms[AA], x, y, z), grad(this->perms[BA], x-1, y, z)), lerp(u, grad(this->perms[AB], x, y-1, z), grad(this->perms[BB], x-1, y-1, z))),	lerp(v, lerp(u, grad(this->perms[AA+1], x, y, z-1), grad(this->perms[BA+1], x-1, y, z-1)), lerp(u, grad(this->perms[AB+1], x, y-1, z-1),	grad(this->perms[BB+1], x-1, y-1, z-1))));
            return (res + 1.0)/2.0;
        }
    private:

        double fade(double t) {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        double lerp(double t, double a, double b) {
            return a + t * (b - a);
        }

        double grad(unsigned int hash, double x, double y, double z) {
            unsigned int h = hash & 15u;
            double u = h < 8 ? x : y,
                    v = h < 4 ? y : h == 12 || h == 14 ? x : z;
            return ((h & 1u) == 0 ? u : -u) + ((h & 2u) == 0 ? v : -v);
        }

        std::vector<int> perms;
    };
}
