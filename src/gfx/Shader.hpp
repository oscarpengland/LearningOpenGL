#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>


class Shader
{
public:
    unsigned int ID;

    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();

    Shader(const Shader &other) = delete;
    Shader(Shader &&other);

    Shader &operator=(const Shader &other) = delete;
    Shader &operator=(Shader &&other);

    void use() const;
    void setMat4(glm::mat4 m, const char *name) const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
};

#endif