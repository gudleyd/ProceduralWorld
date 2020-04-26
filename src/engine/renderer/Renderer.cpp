//
// Created by lebedev-ivan on 26.04.2020.
//

#include "Renderer.h"


namespace gdl {

    void Renderer::render(Camera *camera, Scene *scene) {
        camera->getShader().setUniformMat4f("u_View", camera->getView());
        scene->render(camera);
    }
}