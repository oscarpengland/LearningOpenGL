#version 460 core

struct Material
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColour;

in vec3 normal;
in vec3 lightPos;
in vec3 fragPos;

uniform Light light;
uniform Material material;

void main()
{
    vec3 lightDir = normalize(lightPos - fragPos);

    vec3 ambient = light.ambient * material.diffuse;

    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;

    // Note that view position is the origin as we transfered everything into view space.
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;

    vec3 result = ambient + diffuse + specular;
    FragColour = vec4(result, 1.0);
}