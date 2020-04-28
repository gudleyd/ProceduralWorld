//
// Created by lebedev-ivan on 27.04.2020.
//

#include "HeightMap.h"

#include <fstream>
#include "../procedural/PerlinNoise.h"


namespace gdl {

    HeightMap::HeightMap(const std::string &path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("No file at path " + path);
        if (data != nullptr) free(data);
        file.read(reinterpret_cast<char *>(&width), sizeof(int));
        file.read(reinterpret_cast<char *>(&height), sizeof(int));
        int size = width * height;
        data = static_cast<float *>(malloc(sizeof(float) * size));
        file.read(reinterpret_cast<char *>(&data), sizeof(float) * size);
        file.close();
    }

    HeightMap::~HeightMap() {
        if (data != nullptr)
            free(data);
    }

    void HeightMap::write(const std::string &path) {
        std::ofstream file(path, std::ios::binary);
        file.write(reinterpret_cast<char*>(&width), sizeof(int));
        file.write(reinterpret_cast<char*>(&height), sizeof(int));
        file.write(reinterpret_cast<char*>(&height), sizeof(int) * width * height);
        file.close();
    }

    void HeightMap::generate(int w, int h, float scale, int offsetX, int offsetY) {
        if (data != nullptr) free(data);
        width = w;
        height = h;
        data = static_cast<float *>(malloc(sizeof(float) * width * height));
        PerlinNoise pn(57u);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                data[i * height + j] = pn.noise(scale * (i + offsetX) / width, scale * (j + offsetY) / height, 1.0f);
            }
        }
    }

    float HeightMap::get(int x, int z) {
        return data[x * height + z];
    }

    int HeightMap::getWidth() {
        return width;
    }

    int HeightMap::getHeight() {
        return height;
    }
}