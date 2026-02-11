#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <cstddef>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh
{
private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    GLsizei n_indices = 0;

public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh(Mesh &&other) noexcept;

    Mesh &operator=(const Mesh&) = delete;
    Mesh &operator=(Mesh&&) noexcept;

    void draw() const;
};

#endif