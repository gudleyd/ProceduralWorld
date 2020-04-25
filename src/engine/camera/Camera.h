//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "../time-manager/TimeManager.h"


namespace gdl {

    enum CameraMovementDirection {
        Forward,
        Right,
        Backward,
        Left
    };

    class Camera {
    public:
        Camera();

        void update();

        void move(const glm::vec3& offset);
        void move(CameraMovementDirection, const TimeManager&);
        void mouseRotation(float x, float y);

        void setSpeed(float);
        [[nodiscard]] float getSpeed() const;

        void setSensitivity(float);
        [[nodiscard]] float getSensitivity() const;

        void setY(float);

        [[nodiscard]] const glm::mat4& getView() const;
        [[nodiscard]] const glm::vec3& getPos() const;

    private:
        glm::mat4 view;
        glm::vec3 position, front, up, right, worldUp;
        float pitch;
        float speed;
        float sensitivity;
        float fov;
        float yaw;
    };

}
