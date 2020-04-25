//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Camera.h"


namespace gdl {

    Camera::Camera() {
        this->position = {0.0f, 0.0f, 0.0f};
        this->pitch = 0.0f;
        this->fov = 45.0f;
        this->yaw = -90.0f;
        this->speed = 50.0f;
        this->sensitivity = 0.1f;
        this->worldUp = {0.0f, 1.0f, 0.0f};
        this->front = {0.0f, 0.0f, -1.0f};

        this->update();
    }

    void Camera::update() {
        this->front.x = std::cos(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
        this->front.y = std::sin(glm::radians(this->pitch));
        this->front.z = std::sin(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));
        this->front = glm::normalize(this->front);

        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));

        this->view = glm::lookAt(this->position, this->position + this->front, this->up);
    }

    void Camera::move(const glm::vec3& offset) {
        this->position += offset;
    }

    void Camera::move(CameraMovementDirection direction, const TimeManager& tm) {
        float velocity = this->speed * tm.timeSinceLastTick();

        switch (direction) {
            case Forward: this->position += this->front * velocity; break;
            case Backward: this->position -= this->front * velocity; break;
            case Right: this->position += this->right * velocity; break;
            case Left: this->position -= this->right * velocity; break;
        }
    }

    void Camera::mouseRotation(float x, float y) {
        x *= this->sensitivity;
        y *= this->sensitivity;

        this->yaw = glm::mod(this->yaw + x, 360.0f);
        this->pitch += y;
    }

    void Camera::setSpeed(float newSpeed) {
        this->speed = newSpeed;
    }

    float Camera::getSpeed() const {
        return this->speed;
    }

    void Camera::setSensitivity(float newSensitivity) {
        this->sensitivity = newSensitivity;
    }

    float Camera::getSensitivity() const {
        return this->sensitivity;
    }

    void Camera::setY(float y) {
        this->position.y = y;
    }

    const glm::mat4& Camera::getView() const {
        return this->view;
    }

    const glm::vec3& Camera::getPos() const {
        return this->position;
    }

}