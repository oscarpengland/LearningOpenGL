#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
    GLuint ID = 0;

    Texture(const char* path);
    ~Texture();

    Texture(const Texture &other) = delete;
    Texture(Texture &&other) noexcept;

    Texture &operator=(const Texture &other) = delete;
    Texture &operator=(Texture &&other) noexcept;

    void bind() const;
};

#endif