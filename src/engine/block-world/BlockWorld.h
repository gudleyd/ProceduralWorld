//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../mesh/Mesh.h"
#include "../camera/Camera.h"
#include "../entities/Entities.h"
#include "../scene/Scene.h"
#include "../time-manager/TimeManager.h"
#include "chunk/Chunk.h"


namespace gdl {

    struct BlockWorldSize {
        BlockWorldSize(int x, int y): x(x), y(y) { };
        int x, y;
    };

    class BlockWorld: public IRenderable {
    public:
        BlockWorld();
        explicit BlockWorld(BlockWorldSize size): size(size) { };
        void render(Camera *camera) override;
        void update(const TimeManager& tm, GLFWwindow* window) override;
    private:
        float scale = 2.0f;
        void generate();
        BlockWorldSize size;
        std::vector<Chunk> chunks;
        glm::mat4 model;
    };
}
