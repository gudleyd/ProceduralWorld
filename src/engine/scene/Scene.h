//
// Created by lebedev-ivan on 26.04.2020.
//

#pragma once

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../time-manager/TimeManager.h"
#include "../entities/Entities.h"
#include "../light/Light.h"
#include "../mesh/Mesh.h"

namespace gdl {

    class Scene {
    public:
        Scene() = default;
        void render(Camera*);
        void update(const TimeManager&, GLFWwindow* window);
        void addObject(std::shared_ptr<IRenderable> newObject);
    public:
        std::vector<std::shared_ptr<IRenderable>> objects;
        LightSource lightSource = LightSource(Color(1.0, 1.0, 1.0, 1.0), glm::vec3{0, 10.0, 0}, 1.0);
    };
}
