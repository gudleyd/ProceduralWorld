//
// Created by lebedev-ivan on 26.04.2020.
//

#include "Light.h"


namespace gdl {

    LightSource::LightSource(Color color, glm::vec3 position, glm::vec3 direction, float power): color(color), position(position), direction(direction), power(power) {
    }

    void LightSource::setPosition(glm::vec3 newPos) {
        this->position = newPos;
    }

    const glm::vec3& LightSource::getPosition() const {
        return this->position;
    }

    void LightSource::setDirection(glm::vec3 newDirection) {
        this->direction = newDirection;
    }

    const glm::vec3& LightSource::getDirection() const {
        return this->direction;
    }

    void LightSource::setColor(Color newColor) {
        this->color = newColor;
    }

    const Color& LightSource::getColor() const {
        return this->color;
    }
}