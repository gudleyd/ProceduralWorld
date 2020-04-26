//
// Created by lebedev-ivan on 26.04.2020.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "../entities/Entities.h"

namespace gdl {

    class LightSource {
    public:
        LightSource(Color color, glm::vec3 pos, float power);

        void setPosition(glm::vec3 newPos);
        const glm::vec3& getPosition() const;

        void setColor(Color newColor);
        const Color& getColor() const;
    private:
        Color color;
        glm::vec3 position;
        float power;
    };
}
