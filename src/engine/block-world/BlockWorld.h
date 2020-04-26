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


namespace gdl {

    const Color waterBlockColor = Color(0.0, 0.0, 1.0, 1.0);
    const Color grassBlockColor = Color(0.0, 1.0, 0.0, 1.0);

    struct BlockWorldSize {
        BlockWorldSize(int x, int y, int z): x(x), y(y), z(z) { };
        int x, y, z;
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
        Mesh blockMesh;
        glm::mat4 model;
    };
}
