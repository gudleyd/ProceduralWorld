//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>


namespace gdl {

    class Shader {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        void use() const;
        void stop() const;
        [[nodiscard]] unsigned int getId() const;
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
        void setUniform3f(const std::string& name, float v0, float v1, float v2);

        static void compileShader(unsigned int shaderId, const std::string& shaderCode);
        static std::string readShaderCode(const std::string& path);
    private:
        unsigned int program;
        std::unordered_map<std::string, GLint> attribCache;

        GLint getAttribLocation(const std::string& name);
    };
}
