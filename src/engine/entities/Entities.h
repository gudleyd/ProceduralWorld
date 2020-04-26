//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include "../camera/Camera.h"

namespace gdl {

    struct Color {
        Color() = default;
        Color(float r, float g, float b, float a): r(r), g(g), b(b), a(a) { };
        float r;
        float g;
        float b;
        float a;
    };

    class IRenderable {
    public:
        virtual void render(Camera*) = 0;
        virtual void update(const TimeManager& tm, GLFWwindow* window) = 0;
    };
}

