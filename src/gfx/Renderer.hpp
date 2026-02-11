#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

/* Handles all OpenGL state machine calls to avoid cluttering the main loop.*/
class Renderer
{
private:
    glm::vec4 clear_colour{0.5f, 0.5f, 0.5f, 1.0f};
public:
    void begin_frame() const;
    void draw(const Mesh &mesh, const Material &material, const Shader &shader, const Light &light, const Texture &texture, const Transform& model, const Camera& cam) const;
    void draw(const Mesh &mesh, const Light &light, const Shader &shader, const Camera& cam) const;
    void set_clear_colour(float r, float g, float b);
};

#endif