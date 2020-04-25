//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gdl {

    class TimeManager {
    public:
        TimeManager();
        void tick();
        [[nodiscard]] double timeSinceLastTick() const;
        [[nodiscard]] double framesPerSecond() const;
    private:
        double timeNow;
        double timeLast;
    };
}
