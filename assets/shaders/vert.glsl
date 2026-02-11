#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 lightPos;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 worldLightPos;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    fragPos = vec3(view * model * vec4(aPos, 1.0));
    lightPos = vec3(view * vec4(worldLightPos, 1.0));
    normal = mat3(transpose(inverse(view * model))) * aNormal;
}