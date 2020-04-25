//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include "../time-manager/TimeManager.h"

namespace gdl {

    class Entity {
    public:
        Entity() = default;
        virtual void render() {  };
        virtual void update(const TimeManager& tm) {  };
    };
}
