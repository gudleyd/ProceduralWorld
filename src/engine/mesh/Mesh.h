//
// Created by lebedev-ivan on 26.04.2020.
//

#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "../entities/Entities.h"
#include "../camera/Camera.h"

namespace gdl {

    class Mesh {
    public:
        Mesh();
        ~Mesh();
        void addBlock(float x, float y, float z, float size, const Color& color, uint8_t faces = 63);
        void render(Camera*);
        void clear();

        static void mergeMeshes(Mesh& m1, const Mesh& m2);
    private:
        GLuint vbo_cube_vertices = 0, vbo_cube_colors = 0, vbo_cube_normals = 0;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> colors;
        std::vector<GLfloat> normals;
    };

}
