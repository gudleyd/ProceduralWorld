//
// Created by lebedev-ivan on 26.04.2020.
//

#pragma once

#include "../camera/Camera.h"
#include "../scene/Scene.h"


namespace gdl {

    class WindowController;

    class Renderer {
    public:
        Renderer(WindowController *windowController): windowController(windowController) { };
        void render(Camera *camera, Scene *scene);
    private:
        WindowController *windowController = nullptr;
    };
}