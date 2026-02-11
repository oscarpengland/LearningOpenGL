#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

struct Transform
{
    glm::vec3 pos {0.0f};
    glm::vec3 rotEuler {0.0f};
    glm::vec3 scale {1.0f};

    glm::mat4 model_matrix() const
    {
        glm::mat4 model (1.0f);
        model = glm::translate(model, pos);
        model = glm::rotate(model, rotEuler.x, {1.0f, 0.0f, 0.0f});
        model = glm::rotate(model, rotEuler.y, {0.0f, 1.0f, 0.0f});
        model = glm::rotate(model, rotEuler.z, {0.0f, 0.0f, 1.0f});
        model = glm::scale(model, scale);

        return model;
    }
};

#endif