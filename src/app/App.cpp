#include "App.hpp"
#include <filesystem>

App::App(int width, int height, const std::string &title)
    :  window (nullptr), width (width), height (height), cursor_x ((float)width / 2.0f), cursor_y ((float)height / 2.0f), camera (45.0, width, height, 0.1f, 30.0f)
{
    init_glfw();
    open_window(title);
    init_glad();
    set_gl_state();
    init_callbacks();

    camera.pos = glm::vec3(0.0f, 0.0f, 3.0f);
}

App::~App()
{  
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void App::run()
{
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{ 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{ 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{-0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
                   
        {{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f}},
                      
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
                   
        {{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}},
        {{ 0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}},
        
        {{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}},
        
        {{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}},
        {{ 0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}}
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };

    // Note that the program is run from the root directory.
    std::cout << "CWD: " << std::filesystem::current_path().string() << std::endl;

    Texture texture("assets/textures/container.jpg");
    
    // Object
    Shader shader("assets/shaders/vert.glsl","assets/shaders/frag.glsl");
    Material material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
    Mesh cube(vertices, indices); // TODO: Add scenes.
    Transform modelcube; // TODO: Get rid of transforms.
    
    // Light source
    Shader lightShader("assets/shaders/vert.glsl", "assets/shaders/fraglight.glsl");

    Transform modelLightSource;
    modelLightSource.pos = glm::vec3(2.0f, 2.0f, 1.0f);
    modelLightSource.scale = glm::vec3(0.6f, 0.6f, 0.6f);

    Light light(
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        modelLightSource      
    );

    Renderer renderer;
    renderer.set_clear_colour(0.1f, 0.1f, 0.1f);

    float avg_delta_time {0.0f};
    int i {0};

    float last_frame {0.0f};
    while (!glfwWindowShouldClose(window))
    {
        float current_frame {(float)glfwGetTime()};
        float delta_time {current_frame - last_frame};
        last_frame = current_frame;

        proccessInput(camera, delta_time);

        renderer.begin_frame();

        renderer.draw(cube, material, shader, light, texture, modelcube, camera);

        renderer.draw(cube, light, lightShader, camera);
        
        glfwSwapBuffers(window);
        glfwPollEvents();

        avg_delta_time += delta_time;
        ++i;
    }

    avg_delta_time /= (float)i;
    std::cout << "Average FPS = " << (1.0f / avg_delta_time) << std::endl;
}

void App::init_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void App::init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD.\n";
        glfwTerminate();
        throw("Failed to load GLAD");
    }
}

void App::open_window(const std::string &title)
{
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR: Window failed to load.\n";
        glfwTerminate();
        throw("Failed to load GLAD");
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);
    
    glfwSetWindowUserPointer(window, this);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void App::set_gl_state()
{
    glViewport(0, 0, width, height);
}

void App::proccessInput(Camera &cam, float delta_time)
{
    float camera_speed {1.5f * delta_time};
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.pos += cam.front * camera_speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.pos -= cam.front * camera_speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.pos -= glm::normalize(glm::cross(cam.front, cam.up)) * camera_speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cam.pos += glm::normalize(glm::cross(cam.front, cam.up)) * camera_speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.pos += cam.up * camera_speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.pos -= cam.up * camera_speed;
}

void App::init_callbacks()
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
}

// Callbacks:
void App::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // App *app = static_cast<App*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);

    // TODO: app->camera.recompute_proj();
}

void App::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    App *app = static_cast<App*>(glfwGetWindowUserPointer(window));

    float x_offset = xpos - app->cursor_x;
    float y_offset = app->cursor_y - ypos; // Note that y coordinates range from bottom to top so we must reverse this.
    app->cursor_x = xpos;
    app->cursor_y = ypos;

    const float sensitivity = 0.05f;
    x_offset *= sensitivity;
    y_offset *= sensitivity;

    if (app->firstMouse)
    {
        x_offset = 0.0f;
        y_offset = 0.0f;
        app->firstMouse = false;
    }

    app->camera.pitch += y_offset;
    app->camera.yaw += x_offset;

    if (app->camera.pitch > 89.0f) app->camera.pitch = 89.0f;
    if (app->camera.pitch < -89.0f) app->camera.pitch = -89.0f;

    app->camera.calculate_direction();
}