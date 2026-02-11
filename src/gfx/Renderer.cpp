#include "Renderer.hpp"
#include <iostream>

void Renderer::set_clear_colour(float r, float g, float b)
{
    clear_colour = glm::vec4(r, g, b, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::begin_frame() const
{
    glClearColor(clear_colour.x, clear_colour.y, clear_colour.z, clear_colour.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const Mesh &mesh, const Material &material, const Shader &shader, const Light &light, const Texture &texture, const Transform& model, const Camera& cam) const
{
    shader.use();
    material.bind(shader);
    shader.setMat4(model.model_matrix(), "model");
    shader.setMat4(cam.calculate_view(), "view");
    shader.setMat4(cam.proj, "proj");
    shader.setVec3("worldLightPos", light.model->pos);
    shader.setVec3("light.ambient", light.ambient);
    shader.setVec3("light.diffuse", light.diffuse);
    shader.setVec3("light.specular", light.specular);
    mesh.draw();
}

void Renderer::draw(const Mesh &mesh, const Light &light, const Shader &shader, const Camera& cam) const
{
    shader.use();
    shader.setMat4(light.model->model_matrix(), "model");
    shader.setMat4(cam.calculate_view(), "view");
    shader.setMat4(cam.proj, "proj");
    mesh.draw();
}