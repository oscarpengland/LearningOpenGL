#include "Texture.hpp"

#include <stb_image.h>
#include <iostream>

Texture::Texture(const char *path)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR: Failed to load texture.\n"; 
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    if (ID != 0)
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}

Texture::Texture(Texture &&other) noexcept
    : ID(other.ID)
{
    other.ID = 0;
}

Texture &Texture::operator=(Texture &&other) noexcept
{
    if (this == &other) return *this;

    if (ID) glDeleteTextures(1, &ID);
    ID = other.ID;
    other.ID = 0;

    return *this;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}