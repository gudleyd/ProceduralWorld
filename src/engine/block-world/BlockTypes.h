//
// Created by lebedev-ivan on 28.04.2020.
//

#pragma once

#include <cctype>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "../entities/Entities.h"


namespace gdl {

    enum BlockType: GLint {
        Water = 0,
        Grass = 1,
        Stone = 2
    };

    glm::vec3 COLORS[3] = {{0.0, 0.0, 1.0},
                           {0.0, 1.0, 0.0},
                           {0.6, 0.6, 0.6}};
}