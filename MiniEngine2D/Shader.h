#pragma once
#include <glad/glad.h>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, float x, float y, float z);
    void setMat4(const std::string& name, const float* value);
    ~Shader();

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
    std::string readFile(const char* path);
};