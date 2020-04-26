//
// Created by lebedev-ivan on 26.04.2020.
//

#include "Scene.h"


namespace gdl {

    void Scene::render(Camera *camera) {
        Color lightColor = this->lightSource.getColor();
        camera->getShader().setUniform3f("u_LightColor", lightColor.r, lightColor.g, lightColor.b);
        glm::vec3 lightPos = this->lightSource.getPosition();
        camera->getShader().setUniform3f("u_LightPos", lightPos.x, lightPos.y, lightPos.z);
        for (const auto& obj: this->objects) {
            obj->render(camera);
        }
    }

    void Scene::update(const TimeManager& tm, GLFWwindow* window) {
        for (const auto& obj: this->objects) {
            obj->update(tm, window);
        }
    }

    void Scene::addObject(std::shared_ptr<IRenderable> newObject) {
        this->objects.emplace_back(std::move(newObject));
    }
}