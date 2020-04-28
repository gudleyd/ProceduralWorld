//
// Created by lebedev-ivan on 25.04.2020.
//

#include <iostream>
#include "BlockWorld.h"

#include "../procedural/PerlinNoise.h"
#include "../events/Events.h"
#include "../heightmap/HeightMap.h"


namespace gdl {

    BlockWorld::BlockWorld(): size(BlockWorldSize(8, 8)) {
        this->model = glm::scale(glm::mat4{1.0f}, glm::vec3{0.1f});
        for (int i = 0; i < size.x * size.y; ++i) {
            chunks.emplace_back(Chunk(ChunkSize(64, 64, 64)));
        }
        this->generate();
    }

    void BlockWorld::render(Camera *camera) {
        camera->getShader().setUniformMat4f("u_Model", this->model);
        for (auto& chunk: chunks) {
            chunk.render(camera);
        }
    }

    void BlockWorld::update(const TimeManager& tm, GLFWwindow* window) {
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::KpAdd)) {
            this->scale *= 0.75f;
            this->generate();
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::KpSubtract)) {
            this->scale *= 1.33f;
            this->generate();
        }
    }

    void BlockWorld::generate() {
        for (int i = 0; i < size.x; ++i) {
            for (int j = 0; j < size.y; ++j) {
                chunks[i * size.y + j].generate(i * 64, j * 64, scale);
            }
        }
    }

}