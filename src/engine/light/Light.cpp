//
// Created by lebedev-ivan on 26.04.2020.
//

#include "Light.h"


namespace gdl {

    LightSource::LightSource(Color color, glm::vec3 pos, float power): color(color), position(pos), power(power) {
    }

    void LightSource::setPosition(glm::vec3 newPos) {
        this->position = newPos;
    }

    const glm::vec3& LightSource::getPosition() const {
        return this->position;
    }

    void LightSource::setColor(Color newColor) {
        this->color = newColor;
    }

    const Color& LightSource::getColor() const {
        return this->color;
    }
}