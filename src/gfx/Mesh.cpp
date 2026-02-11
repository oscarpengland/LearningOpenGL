#include "Mesh.hpp"

#include <utility>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
{
    n_indices = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Mesh::draw() const
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, n_indices, GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
    if (EBO) glDeleteBuffers(1, &EBO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

Mesh::Mesh(Mesh &&other) noexcept
{
    VAO = std::exchange(other.VAO, 0);
    VBO = std::exchange(other.VBO, 0);
    EBO = std::exchange(other.EBO, 0);
    n_indices = std::exchange(other.n_indices, 0);         
}

Mesh &Mesh::operator=(Mesh &&other) noexcept
{
    if (this == &other) return *this;

    if (EBO) glDeleteBuffers(1, &EBO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);

    VAO = std::exchange(other.VAO, 0);
    VBO = std::exchange(other.VBO, 0);
    EBO = std::exchange(other.EBO, 0);
    n_indices = std::exchange(other.n_indices, 0);

    return *this;
}