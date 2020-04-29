//
// Created by lebedev-ivan on 25.04.2020.
//

#include "BlockWorld.h"

#include <thread>

#include "../events/Events.h"


namespace gdl {

    BlockWorld::BlockWorld(): size(BlockWorldSize(10, 10)) {
        this->model = glm::scale(glm::mat4{1.0f}, glm::vec3{0.1f});
        for (int i = 0; i < size.x * size.y; ++i) {
            chunks.emplace_back(ChunkSize(256, 256, 256));
        }
        this->generate();
    }

    void BlockWorld::render(Camera *camera) {
        GLuint samplerLocation = glGetUniformLocation(camera->getShader().getId(), "colorRamp");
        glUniform1i(samplerLocation, 0);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_1D, BlockGlobals::shared().getId());
        camera->getShader().setUniformMat4f("u_Model", this->model);
        for (auto& chunk: chunks) {
            chunk.render(camera);
        }
    }

    void BlockWorld::update(const TimeManager& tm, GLFWwindow* window) {
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::KpAdd)) {
            this->scale *= 0.75f;
            this->generate(0, 0);
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::KpSubtract)) {
            this->scale *= 1.33f;
            this->generate(0, 0);
        }
    }

    void BlockWorld::generate(float offsetX, float offsetY) {
        std::vector<std::thread> threads;
        for (int i = 0; i < size.x; ++i) {
            for (int j = 0; j < size.y; ++j) {
                threads.emplace_back(&Chunk::generate, std::ref(chunks[i * size.y + j]), i * 256, j * 256, scale, offsetX, offsetY);
            }
        }
        for (auto& t: threads)
            t.join();
    }

}