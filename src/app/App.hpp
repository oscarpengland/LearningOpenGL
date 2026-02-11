#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "../gfx/Renderer.hpp"

#include <iostream>
#include <string>
#include <vector>

class App
{
public:
    App(int width, int height, const std::string &title);
    ~App();

    // We shouldn't really have to manipulate more than one instance of app at a time so we don't need copy/move ctors/assignment.
    App(const App &other) = delete;
    App(App &&other) = delete;
    App &operator=(const App &other) = delete;
    App &operator=(App &&other) = delete;


    void run();
private:

    GLFWwindow *window;

    int width, height;
    float cursor_x, cursor_y;
    bool firstMouse {true};

    Camera camera;

    void init_glfw();
    void init_glad();
    void open_window(const std::string &title);
    void init_callbacks();
    void set_gl_state();
    
    void proccessInput(Camera &cam, float delta_time);

    // Callback functions:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
};

#endif