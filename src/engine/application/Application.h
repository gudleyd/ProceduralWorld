//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <cstring>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../time-manager/TimeManager.h"
#include "../shader/Shader.h"
#include "../controllers/Controllers.h"
#include "../scene/Scene.h"
#include "../block-world/BlockWorld.h"


namespace gdl {

    class Application {
    public:
        Application();
        void run();
    private:
        GLFWwindow* mainWindow;
    };
}