//
// Created by lebedev-ivan on 25.04.2020.
//

#include <iostream>
#include "BlockWorld.h"

#include "../procedural/PerlinNoise.h"
#include "../events/Events.h"
#include "../heightmap/HeightMap.h"


namespace gdl {

    BlockWorld::BlockWorld(): size(BlockWorldSize(256, 64, 256)) {
        this->model = glm::scale(glm::mat4{1.0f}, glm::vec3{0.1f});
        this->generate();
    }

    void BlockWorld::render(Camera *camera) {
        camera->getShader().setUniformMat4f("u_Model", this->model);
        this->blockMesh.render(camera);
    }

    void BlockWorld::update(const TimeManager& tm, GLFWwindow* window) {
        if (glfwGetKey(window, (int)gdl::KeyboardKey::KpAdd) == GLFW_PRESS) {
            this->scale *= 0.75f;
            this->blockMesh.clear();
            this->generate();
        }
        if (glfwGetKey(window, (int)gdl::KeyboardKey::KpSubtract) == GLFW_PRESS) {
            this->scale *= 1.33f;
            this->blockMesh.clear();
            this->generate();
        }
    }

    void BlockWorld::setOffset(int newOffsetX, int newOffsetZ) {
        this->offsetZ = newOffsetZ;
        this->offsetX = newOffsetX;
        this->blockMesh.clear();
        this->generate();
    }

    void BlockWorld::generate() {
        double time = glfwGetTime();
        float height[size.x][size.z];
        Color color[size.x][size.z];
        HeightMap hm;
        hm.generate(size.x, size.z, scale);
        for (int x = 0; x < size.x; ++x) {
            for (int z = 0; z < size.z; ++z) {
                float n = floor(size.y * hm.get(z, x));
                if (n <= 20) {
                    height[x][z] = 20;
                    color[x][z] = waterBlockColor;
                } else if (n < 40) {
                    height[x][z] = n;
                    color[x][z] = grassBlockColor;
                } else {
                    height[x][z] = n;
                    color[x][z] = stoneBlockColor;
                }
            }
        }
        unsigned int faces = 0;
        for (int x = 0; x < size.x; ++x) {
            for (int z = 0; z < size.z; ++z) {
                faces = 16;
                if (x - 1 >= 0 && height[x - 1][z] < height[x][z]) faces |= 8u;
                if (x + 1 < size.x && height[x + 1][z] < height[x][z]) faces |= 4u;
                if (z - 1 >= 0 && height[x][z - 1] < height[x][z]) faces |= 2u;
                if (z + 1 < size.z && height[x][z + 1] < height[x][z]) faces |= 1u;
                this->blockMesh.addBlock(x + offsetX, height[x][z], z + offsetZ, 1.0, color[x][z], faces);
            }
        }
    }

}