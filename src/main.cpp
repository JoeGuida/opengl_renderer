#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "camera.hpp"
#include "cylinder.hpp"
#include "filesystem.hpp"
#include "icosahedron.hpp"
#include "light.hpp"
#include "octahedron.hpp"
#include "rectangle.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "sphere.hpp"
#include "tetrahedron.hpp"

#include <iostream>

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initialize_window();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void move_camera();
void process_input(GLFWwindow* window);

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr double ASPECT_RATIO = SCREEN_WIDTH / static_cast<float>(SCREEN_HEIGHT);

bool mouse_button_pressed = false;
double last_x = SCREEN_WIDTH / 2.0;
double last_y = SCREEN_HEIGHT / 2.0;
glm::vec2 cursor_delta(0.0f);

constexpr glm::vec3 world_up(0.0f, 1.0f, 0.0f);

Camera camera(
    glm::vec3(0.0f, 0.0f, -1.0f),
    world_up,
    glm::radians(90.0f),
    Transform(glm::vec3(0.0f, 0.0f, 3.0f))
);
constexpr float CAMERA_MOVEMENT_VELOCITY = 6.0f;
constexpr float CAMERA_ROTATION_VELOCITY = 200.0f;

bool wireframe = false;
bool move_forward = false;
bool move_back = false;
bool move_left = false;
bool move_right = false;
bool move_up = false;
bool move_down = false;

float delta_time = 0.0f;
float last_frame_time = 0.0f;
float current_frame_time = 0.0f;

int main() {
    GLFWwindow* window = initialize_window();
    Renderer::initialize();

    Shader phong_shader(
        FileSystem::get_path("/src/shaders/phong.vert"),
        FileSystem::get_path("/src/shaders/phong.frag"));
    Shader light_shader(
        FileSystem::get_path("/src/shaders/light.vert"),
        FileSystem::get_path("/src/shaders/light.frag"));

    AmbientLight ambient_light(0.2f);
    PointLight point_light(glm::vec3(4.0f, 1.0f, 1.0f), 0.5f);
    Sphere light_sphere(0.2f, 3, WHITE_MATERIAL, Transform(point_light.position));

    phong_shader.set_uniform("ambient", ambient_light.intensity);
    phong_shader.set_uniform("light_pos", point_light.position);
    phong_shader.set_uniform("light_intensity", point_light.intensity);

    Cylinder cylinder(0.5f, 1.0f, 32, BLUE_MATERIAL, Transform(glm::vec3(0.0f, 0.0f, 0.0f)));
    Icosahedron icosahedron(0.5f, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), YELLOW_MATERIAL);
    Octahedron octahedron(0.5f, VIOLET_MATERIAL, Transform(glm::vec3(-6.0f, 0.0f, 0.0f)));
    Rectangle rectangle(glm::vec3(1.0f), GREEN_MATERIAL, Transform(glm::vec3(2.0f, 0.0f, 0.0f)));
    Sphere sphere(0.5f, 3, RED_MATERIAL, Transform(glm::vec3(4.0f, 0.0f, 0.0f)));
    Tetrahedron tetrahedron(0.5f, CYAN_MATERIAL, Transform(glm::vec3(-4.0f, 0.0f, 0.0f)));

    glm::mat4 view;
    glm::mat4 projection = glm::perspective(static_cast<double>(camera.fov_radians), ASPECT_RATIO, 0.01, 100.0);
    phong_shader.set_uniform("projection", projection);
    light_shader.set_uniform("projection", projection);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        current_frame_time = static_cast<float>(glfwGetTime());
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        move_camera();
        view = glm::lookAt(camera.transform.position, camera.transform.position + camera.front, world_up);
        phong_shader.set_uniform("view", view);
        light_shader.set_uniform("view", view);

        point_light.position += glm::vec3(-0.015f, 0.0f, 0.0f) * sin(static_cast<float>(glfwGetTime()));
        phong_shader.set_uniform("light_pos", point_light.position);
        light_sphere.transform.position += glm::vec3(-0.015f, 0.0f, 0.0f) * sin(static_cast<float>(glfwGetTime()));

        Renderer::draw(cylinder, phong_shader);
        Renderer::draw(icosahedron, phong_shader);
        Renderer::draw(octahedron, phong_shader);
        Renderer::draw(rectangle, phong_shader);
        Renderer::draw(sphere, phong_shader, sphere.depth);
        Renderer::draw(tetrahedron, phong_shader);

        Renderer::draw(light_sphere, light_shader, light_sphere.depth);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    double x_diff = (xpos - last_x) / SCREEN_HEIGHT;
    double y_diff = (ypos - last_y) / SCREEN_WIDTH;
    x_diff = (fabs(x_diff) > 0.01f) ? x_diff : 0.0f;
    y_diff = (fabs(y_diff) > 0.01f) ? y_diff : 0.0f;

    cursor_delta = glm::vec2(x_diff, y_diff);

    last_x = xpos;
    last_y = ypos;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initialize_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Renderer", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);

    return window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        wireframe = !wireframe;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouse_button_pressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouse_button_pressed = false;
    }
}

void move_camera() {
    if (mouse_button_pressed) {
        camera.rotate(cursor_delta * CAMERA_ROTATION_VELOCITY * -1.0f * delta_time);
    }
    if (move_forward) {
        camera.transform.position += camera.front * CAMERA_MOVEMENT_VELOCITY * delta_time;
    }
    if (move_back) {
        camera.transform.position -= camera.front * CAMERA_MOVEMENT_VELOCITY * delta_time;
    }
    if (move_left) {
        camera.transform.position -= camera.right * CAMERA_MOVEMENT_VELOCITY * delta_time;
    }
    if (move_right) {
        camera.transform.position += camera.right * CAMERA_MOVEMENT_VELOCITY * delta_time;
    }
    if (move_up) {
        camera.transform.position += world_up * CAMERA_MOVEMENT_VELOCITY * delta_time;
    }
    if (move_down) {
        camera.transform.position -= world_up * CAMERA_MOVEMENT_VELOCITY * delta_time;
    }
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        move_forward = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
        move_forward = false;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        move_back = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        move_back = false;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        move_left = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        move_left = false;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        move_right = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        move_right = false;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        move_up = true;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
        move_up = false;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        move_down = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
        move_down = false;
    }
}
