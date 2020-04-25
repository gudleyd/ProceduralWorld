//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Shader.h"


namespace gdl {

    Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
        std::string vertexShaderCode = Shader::readShaderCode(vertexShaderPath);
        std::string fragmentShaderCode = Shader::readShaderCode(fragmentShaderPath);

        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        Shader::compileShader(vertexShaderId, vertexShaderCode);
        Shader::compileShader(fragmentShaderId, fragmentShaderCode);

        this->program = glCreateProgram();

        glAttachShader(this->program, vertexShaderId);
        glAttachShader(this->program, fragmentShaderId);
        glLinkProgram(this->program);
        glDetachShader(this->program, vertexShaderId);
        glDetachShader(this->program, fragmentShaderId);
        glValidateProgram(this->program);

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    void Shader::use() const {
        glUseProgram(this->program);
    }

    void Shader::stop() const {
        glDeleteProgram(this->program);
    }

    unsigned int Shader::getId() const {
        return this->program;
    }

    void Shader::compileShader(unsigned int shaderId, const std::string &shaderCode) {
        const char* sourceCode = shaderCode.c_str();
        glShaderSource(shaderId, 1, &sourceCode, nullptr);
        glCompileShader(shaderId);

        // Todo:: Make debug only
        GLint result = GL_FALSE;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        if (result != GL_TRUE) {
            throw std::runtime_error("Cannot compile shader with id " + std::to_string(shaderId));
        }
    }

    std::string Shader::readShaderCode(const std::string &path) {
        std::string shaderCode;
        std::ifstream shaderFile(path);
        if (shaderFile.is_open()) {
            std::stringstream tmp;
            tmp << shaderFile.rdbuf();
            shaderCode = tmp.str();
            shaderFile.close();
        } else {
            throw std::runtime_error("Cannot open shader on " + path);
        }
        return shaderCode;
    }

    void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const {
        glUniform4f(glGetUniformLocation(this->program, name.c_str()), v0, v1, v2, v3);
    }

    void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) const {
        glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
    }
}