//
// Created by lebedev-ivan on 26.04.2020.
//

#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <string>

#include "../entities/Entities.h"
#include "../camera/Camera.h"

namespace gdl {

    class Mesh {
    public:
        Mesh();

        void addBlock(float x, float y, float z, float size, float colorIndex, uint8_t faces = 63);
        void render(Camera*);
        void clear();
        void deleteBuffers();

        static void mergeMeshes(Mesh& m1, const Mesh& m2);
    private:
        GLuint vbo_cube_vertices = 0, vbo_cube_colors = 0, vbo_cube_normals = 0;
        bool needRebind = true;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> colors;
    };

}
