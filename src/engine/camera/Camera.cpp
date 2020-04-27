//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Camera.h"


namespace gdl {

    Camera::Camera(): shader(Shader("../resources/shaders/shader.vert", "../resources/shaders/shader.frag")) {
        this->position = {-7.0f, 27.0f, -14.5f};
        this->pitch = -23.8f;
        this->fov = 45.0f;
        this->yaw = 49.0f;
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

    const glm::vec3& Camera::getDirection() {
        return this->front;
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
            case Up: this->position += this->up * velocity; break;
            case Down: this->position -= this->up * velocity; break;
        }
    }

    void Camera::mouseRotation(float x, float y) {
        x *= this->sensitivity;
        y *= this->sensitivity;

        this->yaw = glm::mod(this->yaw + x, 360.0f);
        this->pitch += y;

        if (this->pitch > 89.9f) this->pitch = 89.9f;
        if (this->pitch < -89.9f) this->pitch = -89.9f;

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

    float Camera::getFov() const {
        return this->fov;
    }

    void Camera::setShader(const Shader& sh) {
        this->shader = sh;
    }

    float Camera::getPitch() {
        return this->pitch;
    }

    float Camera::getYaw() {
        return this->yaw;
    }

    Shader& Camera::getShader() {
        return this->shader;
    }

    void Camera::setX(float x) {
        this->position.x = x;
    }

    void Camera::setY(float y) {
        this->position.y = y;
    }

    void Camera::setZ(float z) {
        this->position.z = z;
    }

    const glm::mat4& Camera::getView() const {
        return this->view;
    }

    const glm::vec3& Camera::getPos() const {
        return this->position;
    }

}