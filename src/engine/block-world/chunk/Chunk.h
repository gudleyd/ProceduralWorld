//
// Created by lebedev-ivan on 27.04.2020.
//

#pragma once

#include "../../mesh/Mesh.h"

namespace gdl {

    const Color waterBlockColor = Color(0.0, 0.0, 1.0, 1.0);
    const Color grassBlockColor = Color(0.0, 1.0, 0.0, 1.0);
    const Color stoneBlockColor = Color(149.0f / 255, 148.0f / 255, 139.0f / 255, 1.0);

    struct ChunkSize {
        ChunkSize(int x, int y, int z): x(x), y(y), z(z) { };
        int x, y, z;
    };

    class Chunk {
    public:
        Chunk();
        explicit Chunk(ChunkSize size): size(size) { };
        void render(Camera *camera);
        void generate(int offsetX, int offsetZ, float scale);
    private:
        ChunkSize size;
        Mesh blockMesh;
        glm::mat4 model = glm::scale(glm::mat4{1.0f}, glm::vec3{0.1f});
    };
}
