//
// Created by lebedev-ivan on 28.04.2020.
//

#pragma once

#include <cctype>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

namespace gdl {

    enum BlockType: GLuint {
        Water = 0,
        Grass = 1,
        Stone = 2
    };

    class BlockGlobals {
    public:
        static BlockGlobals& shared() {
            static BlockGlobals s;
            return s;
        }

        GLfloat COLORS[9] = {0.0f, 0.0f, 1.0f, // Water
                             0.0f, 1.0f, 0.0f, // Grass
                             0.5f, 0.5f, 0.5f // Stone
                             };

        GLuint getId() {
            return this->colorMapId;
        }
    private:
        GLuint colorMapId;
        BlockGlobals() {
            glGenTextures(1, &colorMapId);
            glBindTexture(GL_TEXTURE_1D, colorMapId);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            float data[] =
                    {
                            0.0f, 0.0f, 1.0f, 1.0f,
                            0.0f, 1.0f, 0.0f, 1.0f,
                            149.0f / 255, 148.0f / 255, 139.0f / 255, 1.0
                    };

            glTexImage1D(
                    GL_TEXTURE_1D,
                    0,
                    GL_RGBA32F,
                    3,
                    0,
                    GL_RGBA,
                    GL_FLOAT,
                    data
            );

            float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
            glTexParameterfv(GL_TEXTURE_1D, GL_TEXTURE_BORDER_COLOR, borderColor);

            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_1D, 0);
        }
        ~BlockGlobals() {  }

        BlockGlobals(BlockGlobals const&) = delete;
        BlockGlobals& operator= (BlockGlobals const&) = delete;
    };
}