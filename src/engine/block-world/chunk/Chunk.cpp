//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Chunk.h"

#include <iostream>

#include "../../procedural/PerlinNoise.h"
#include "../../heightmap/HeightMap.h"


namespace gdl {

    Chunk::Chunk(): size(ChunkSize(64, 256, 64)) {
        this->model = glm::scale(glm::mat4{1.0f}, glm::vec3{1.0f});
    }

    Chunk::Chunk(ChunkSize chunkSize): size(chunkSize) {
        this->blockMesh = Mesh();
        this->model = glm::scale(glm::mat4{1.0f}, glm::vec3{1.0f});
    }

    void Chunk::render(Camera *camera) {
        this->blockMesh.render(camera);
    }

    void Chunk::generate(float offsetX, float offsetZ, float scale, float mapOffsetX, float mapOffsetZ) {
        this->blockMesh.clear();
        float height[size.x][size.z];
        BlockType color[size.x][size.z];
        HeightMap hm;
        hm.generate(size.x, size.z, scale, offsetX + mapOffsetX, offsetZ + mapOffsetZ);
        for (int x = 0; x < size.x; ++x) {
            for (int z = 0; z < size.z; ++z) {
                float n = floor(size.y * hm.get(x, z) / scale);
                if (n <= 0.3 * size.y / scale) {
                    height[x][z] = 0.3 * size.y / scale;
                    color[x][z] = Water;
                } else if (n < 0.6 * size.y / scale) {
                    height[x][z] = n;
                    color[x][z] = Grass;
                } else {
                    height[x][z] = n;
                    color[x][z] = Stone;
                }
            }
        }
        unsigned int faces = 0;
        for (int x = 0; x < size.x; ++x) {
            for (int z = 0; z < size.z; ++z) {
                faces = 16;
                if (x == 0) faces |= 8u;
                if (z == 0) faces |= 2u;
                if (x == size.x - 1) faces |= 6u;
                if (z == size.z - 1) faces |= 1u;
                if (x - 1 >= 0 && height[x - 1][z] < height[x][z]) faces |= 8u;
                if (x + 1 < size.x && height[x + 1][z] < height[x][z]) faces |= 4u;
                if (z - 1 >= 0 && height[x][z - 1] < height[x][z]) faces |= 2u;
                if (z + 1 < size.z && height[x][z + 1] < height[x][z]) faces |= 1u;
                this->blockMesh.addBlock(x + offsetX, height[x][z], z + offsetZ, 1.0, 1.0f / 3 * color[x][z] + 0.001, faces);
            }
        }
    }

}