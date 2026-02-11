#include "Camera.hpp"

Camera::Camera(float fov, int width, int height, float near, float far)
    : proj {glm::perspective(glm::radians(fov), (float)width/(float)height, near, far)}
{}

void Camera::calculate_direction()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}

glm::mat4 Camera::calculate_view() const
{
    glm::mat4 view;
    view = glm::lookAt(
        pos,
        pos + front,
        up   
    );

    return view;
}