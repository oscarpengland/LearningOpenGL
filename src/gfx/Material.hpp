#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Texture.hpp";
#include "Transform.hpp"

class Material
{
public:
    Texture texture;
    glm::vec3 ambient {0.0f};
    glm::vec3 diffuse {0.0f};
    glm::vec3 specular {0.0f};
    float shininess {0.0f};

    Material(Texture texture, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
        : texture {std::move(texture)}, ambient{std::move(ambient)}, diffuse{std::move(diffuse)}, specular{std::move(specular)}, shininess{std::move(shininess)}
    {}

    /**
     * Note that the shader has to be bound before bind() is called.
     */
    void bind(const Shader &shader) const
    {
        shader.setInt("material.diffuse", texture);
        shader.setVec3("material.specular", specular);
        shader.setFloat("material.shininess", shininess);
    }
};

struct Light
{
    glm::vec3 ambient {0.0f};
    glm::vec3 diffuse {0.0f};
    glm::vec3 specular {0.0f};
    Transform *model;

    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Transform &model)
        : ambient {std::move(ambient)}, diffuse {std::move(diffuse)}, specular {std::move(specular)}, model {&model}
    {}
};

#endif