//
// Created by lebedev-ivan on 25.04.2020.
//

#include "BlockWorld.h"


namespace gdl {

    BlockWorld::BlockWorld() {
        float points[6] = {
                200.0f, 200.0f,
                200.0f, 0.0f,
                200.0f, 200.0f
        };

        unsigned int buffer;

        // Create a buffer
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
    }

    void BlockWorld::render() {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void BlockWorld::update(const TimeManager& tm) {

    }
}