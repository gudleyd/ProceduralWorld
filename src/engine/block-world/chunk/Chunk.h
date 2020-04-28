//
// Created by lebedev-ivan on 27.04.2020.
//

#pragma once

#include "../../mesh/Mesh.h"
#include "../BlockTypes.h"

namespace gdl {

    struct ChunkSize {
        ChunkSize(int x, int y, int z): x(x), y(y), z(z) { };
        int x, y, z;
    };

    class Chunk {
    public:
        Chunk();
        explicit Chunk(ChunkSize size): size(size) { };
        void render(Camera *camera);
        void generate(float offsetX, float offsetZ, float scale, float mapOffsetX = 0, float mapOffsetZ = 0);
    private:
        ChunkSize size;
        Mesh blockMesh;
        glm::mat4 model = glm::scale(glm::mat4{1.0f}, glm::vec3{0.1f});
    };
}
