//
// Created by lebedev-ivan on 26.04.2020.
//

#include <iostream>
#include <thread>

#include "Mesh.h"


namespace gdl {

    Mesh::Mesh() {
        glGenBuffers(1, &vbo_cube_vertices);
        glGenBuffers(1, &vbo_cube_colors);
        glGenBuffers(1, &vbo_cube_normals);
    }

    void Mesh::addBlock(float x, float y, float z, float size, float colorIndex, uint8_t faces) {
        float halfSize = size / 2;
        GLfloat vertexBufferData[6][18] = {
            {(x*size) + -halfSize, (y*size) + -halfSize, (z*size) + halfSize, // front
            (x*size) + -halfSize, (y*size) + halfSize, (z*size) + halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + halfSize,
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + halfSize,
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + halfSize},

            {(x*size) + -halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + -halfSize, // rear
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + -halfSize},

            {(x*size) + halfSize, (y*size) + -halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + halfSize, // right
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + halfSize},

            {(x*size) + -halfSize, (y*size) + -halfSize, (z*size) + halfSize, // left
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + -halfSize,
            (x*size) + -halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + halfSize,
            (x*size) + -halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + -halfSize, (y*size) + halfSize, (z*size) + halfSize},

            {(x*size) + -halfSize, (y*size) + halfSize, (z*size) + halfSize, // top
            (x*size) + -halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + halfSize,
            (x*size) + -halfSize, (y*size) + halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + halfSize, (z*size) + -halfSize},

            {(x*size) + -halfSize, (y*size) + -halfSize, (z*size) + -halfSize,
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + halfSize, // bottom
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + halfSize,
            (x*size) + -halfSize, (y*size) + -halfSize, (z*size) + -halfSize,
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + halfSize,
            (x*size) + halfSize, (y*size) + -halfSize, (z*size) + -halfSize}
        };

        GLfloat normalBufferData[6][18] = {
                {0, 0, 1,
                0, 0, 1,
                0, 0, 1,
                0, 0, 1,
                0, 0, 1,
                0, 0, 1},

                {0, 0, -1,
                0, 0, -1,
                0, 0, -1,
                0, 0, -1,
                0, 0, -1,
                0, 0, -1},

                {1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0,
                1, 0, 0},

                {-1, 0, 0,
                -1, 0, 0,
                -1, 0, 0,
                -1, 0, 0,
                -1, 0, 0,
                -1, 0, 0},

                {0, 1, 0,
                0, 1, 0,
                0, 1, 0,
                0, 1, 0,
                0, 1, 0,
                0, 1, 0},

                {0, -1, 0,
                0, -1, 0,
                0, -1, 0,
                0, -1, 0,
                0, -1, 0,
                0, -1, 0}
        };
        int drownFaces = 0;
        if (faces & 1u) {
            vertices.insert(vertices.end(), vertexBufferData[0], vertexBufferData[0] + 18);
            normals.insert(normals.end(), normalBufferData[0], normalBufferData[0] + 18);
            ++drownFaces;
        }
        if (faces & 2u) {
            vertices.insert(vertices.end(), vertexBufferData[1], vertexBufferData[1] + 18);
            normals.insert(normals.end(), normalBufferData[1], normalBufferData[1] + 18);
            ++drownFaces;
        }
        if (faces & 4u) {
            vertices.insert(vertices.end(), vertexBufferData[2], vertexBufferData[2] + 18);
            normals.insert(normals.end(), normalBufferData[2], normalBufferData[2] + 18);
            ++drownFaces;
        }
        if (faces & 8u) {
            vertices.insert(vertices.end(), vertexBufferData[3], vertexBufferData[3] + 18);
            normals.insert(normals.end(), normalBufferData[3], normalBufferData[3] + 18);
            ++drownFaces;
        }
        if (faces & 16u) {
            vertices.insert(vertices.end(), vertexBufferData[4], vertexBufferData[4] + 18);
            normals.insert(normals.end(), normalBufferData[4], normalBufferData[4] + 18);
            ++drownFaces;
        }
        if (faces & 32u) {
            vertices.insert(vertices.end(), vertexBufferData[5], vertexBufferData[5] + 18);
            normals.insert(normals.end(), normalBufferData[5], normalBufferData[5] + 18);
            ++drownFaces;
        }
        for (int i = 0; i < drownFaces * 6; ++i)
            colors.push_back(colorIndex);

        needRebind = true;

    }

    void Mesh::deleteBuffers() {
        glDeleteBuffers(1, &vbo_cube_vertices);
        glDeleteBuffers(1, &vbo_cube_colors);
        glDeleteBuffers(1, &vbo_cube_normals);
    }

    void Mesh::render(Camera* camera) {

        if (needRebind) {
            const GLfloat *vrts = &(this->vertices[0]);
            const GLfloat *clrs = &(this->colors[0]);
            const GLfloat *nrmls = &(this->normals[0]);

            GLsizeiptr vertexSize = this->vertices.size() * sizeof(GLfloat);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
            glBufferData(GL_ARRAY_BUFFER, vertexSize, vrts, GL_STATIC_DRAW);

            GLsizeiptr normalsSize = this->normals.size() * sizeof(GLfloat);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_normals);
            glBufferData(GL_ARRAY_BUFFER, normalsSize, nrmls, GL_STATIC_DRAW);

            GLsizeiptr colorSize = this->colors.size() * sizeof(GLfloat);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
            glBufferData(GL_ARRAY_BUFFER, colorSize, clrs, GL_STATIC_DRAW);

            needRebind = false;
        }

        GLint attribute_coord3d = glGetAttribLocation(camera->getShader().getId(), "coord3d");
        GLint attribute_normal = glGetAttribLocation(camera->getShader().getId(), "normal");
        GLint attribute_v_color = glGetAttribLocation(camera->getShader().getId(), "colorIndex");

        glEnableVertexAttribArray(attribute_coord3d);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
        glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(attribute_v_color);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
        glVertexAttribPointer(attribute_v_color, 1, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(attribute_normal);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_normals);
        glVertexAttribPointer(attribute_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArraysInstanced(GL_TRIANGLES, 0, this->vertices.size() / 3, 1);

        glDisableVertexAttribArray(attribute_coord3d);
        glDisableVertexAttribArray(attribute_v_color);
        glDisableVertexAttribArray(attribute_normal);
    }

    void Mesh::clear() {
        this->vertices.clear();
        this->colors.clear();
        this->normals.clear();
        needRebind = true;
    }

    void Mesh::mergeMeshes(Mesh &m1, const Mesh &m2) {
        m1.vertices.insert(m1.vertices.end(), m2.vertices.begin(), m2.vertices.end());
        m1.colors.insert(m1.colors.end(), m2.colors.begin(), m2.colors.end());
        m1.normals.insert(m1.normals.end(), m2.normals.begin(), m2.normals.end());
    }
}