//
// Created by lebedev-ivan on 26.04.2020.
//

#include <iostream>
#include "Scene.h"


namespace gdl {

    void Scene::render(Camera *camera) {
        Color lightColor = this->lightSource.getColor();
        camera->getShader().setUniform3f("u_LightColor", lightColor.r, lightColor.g, lightColor.b);
//        glm::vec3 lightPos = this->lightSource.getPosition();
//        camera->getShader().setUniform3f("u_LightPos", lightPos.x, lightPos.y, lightPos.z);
        glm::vec3 lightDir = this->lightSource.getDirection();
        camera->getShader().setUniform3f("u_LightDirection", lightDir.x, lightDir.y, lightDir.z);
        glm::vec3 cameraPos = camera->getPos();
        camera->getShader().setUniform3f("u_ViewPos", cameraPos.x, cameraPos.y, cameraPos.z);
        for (const auto& obj: this->objects) {
            obj->render(camera);
        }
    }

    void Scene::update(const TimeManager& tm, GLFWwindow* window) {
        glm::mat4 rotationMat(1);
        glm::vec3 lightDir = this->lightSource.getDirection();
        rotationMat = glm::rotate(rotationMat, 0.001f, glm::vec3(0.0, 1.0, 0.0));
        lightDir = glm::vec3(rotationMat * glm::vec4(lightDir, 1.0));
        this->lightSource.setDirection(lightDir);
        for (const auto& obj: this->objects) {
            obj->update(tm, window);
        }
    }

    void Scene::addObject(std::shared_ptr<IRenderable> newObject) {
        this->objects.emplace_back(std::move(newObject));
    }
}