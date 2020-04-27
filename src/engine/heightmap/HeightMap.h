//
// Created by lebedev-ivan on 27.04.2020.
//

#pragma once

#include <string>

namespace gdl {

    class HeightMap {
    public:
        HeightMap() = default;
        HeightMap(HeightMap&&) = default;
        HeightMap& operator=(HeightMap&&) = default;
        ~HeightMap();

        HeightMap(const HeightMap&) = delete;
        HeightMap& operator=(const HeightMap&) = delete;

        HeightMap(const std::string& path);

        void write(const std::string& path);

        void generate(int w, int h, float scale);
        float get(int x, int z);

        int getWidth();
        int getHeight();
    private:
        int width = 0, height = 0;
        float* data = nullptr;
    };
}