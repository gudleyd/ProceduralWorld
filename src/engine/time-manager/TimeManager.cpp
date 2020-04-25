//
// Created by lebedev-ivan on 25.04.2020.
//

#include "TimeManager.h"


namespace gdl {

    TimeManager::TimeManager() {
        this->timeNow = this->timeLast = glfwGetTime();
    }

    void TimeManager::tick() {
        this->timeLast = this->timeNow;
        this->timeNow = glfwGetTime();
    }

    double TimeManager::timeSinceLastTick() const {
        return this->timeNow - this->timeLast;
    }

    double TimeManager::framesPerSecond() const {
        return 1.0 / this->timeSinceLastTick();
    }
}