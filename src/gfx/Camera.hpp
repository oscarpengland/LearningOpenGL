#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::mat4 proj;

    glm::vec3 pos {0.0f, 0.0f, 0.0f};
    glm::vec3 front {0.0f, 0.0f, -1.0f};
    glm::vec3 up {0.0f, 1.0f, 0.0f};

    float pitch {0.0f};
    float yaw {-90.0f};

    Camera(float fov, int width, int height, float near, float far);
    void recompute_proj(float fov, int width, int height, float near, float far);
    void calculate_direction();
    glm::mat4 calculate_view() const;
};

#endif