//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../entities/Entity.h"
#include "../time-manager/TimeManager.h"


namespace gdl {

    struct BlockWorldSize {
        size_t x;
        size_t y;
        size_t z;
    };

    class BlockWorld: public Entity {
    public:
        BlockWorld();
        void render() override;
        void update(const TimeManager& tm) override;
    private:
        BlockWorldSize size;
    };
}
