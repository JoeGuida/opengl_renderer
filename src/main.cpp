#define GLM_ENABLE_EXPERIMENTAL

#include "glm/vec3.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "camera.hpp"
#include "cylinder.hpp"
#include "fbo.hpp"
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
constexpr double CAMERA_NEAR = 0.01;
constexpr double CAMERA_FAR = 100.0;

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

    // SHADERS --------------------------------------------------------------------------------------------------------------------------------------

    std::shared_ptr<Shader> blinn_phong = ShaderFactory::create("blinn-phong");
    std::shared_ptr<Shader> g_buffer_shader = ShaderFactory::create("g_buffer");
    std::shared_ptr<Shader> lighting_pass_shader = ShaderFactory::create("lighting_pass");
    std::shared_ptr<Shader> light_shader = ShaderFactory::create("light");
    std::shared_ptr<Shader> quad_shader = ShaderFactory::create("quad");
    
    std::vector<std::shared_ptr<Shader>> shaders{ 
        blinn_phong,
        g_buffer_shader,
        lighting_pass_shader,
        light_shader,
        quad_shader
    };

    // MATERIALS ------------------------------------------------------------------------------------------------------------------------------------

    BRDFMaterial RED_MATERIAL(ShaderFactory::get("g_buffer"),    glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 256);
    BRDFMaterial GREEN_MATERIAL(ShaderFactory::get("g_buffer"),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 256);
    BRDFMaterial BLUE_MATERIAL(ShaderFactory::get("g_buffer"),   glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 256);
    BRDFMaterial YELLOW_MATERIAL(ShaderFactory::get("g_buffer"), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.0f, 256);
    BRDFMaterial VIOLET_MATERIAL(ShaderFactory::get("g_buffer"), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.0f, 256);
    BRDFMaterial CYAN_MATERIAL(ShaderFactory::get("g_buffer"),   glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 0.0f, 256);
    BRDFMaterial WHITE_MATERIAL(ShaderFactory::get("light"),     glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 256);

    // OBJECTS --------------------------------------------------------------------------------------------------------------------------------------

    Cylinder cylinder(0.5f, 1.0f, 32, BLUE_MATERIAL, Transform(glm::vec3(0.0f, 0.0f, 0.0f)));
    Rectangle rectangle(glm::vec3(1.0f), GREEN_MATERIAL, Transform(glm::vec3(2.0f, 0.0f, 0.0f)));
    Rectangle rectangle1(glm::vec3(10.0f, 0.0f, 10.0f), YELLOW_MATERIAL, Transform(glm::vec3(1.25f, -0.485f, 0.0f)));

    // LIGHTS ---------------------------------------------------------------------------------------------------------------------------------------

    AmbientLight ambient_light(0.2f);
    PointLight point_light(rectangle.transform.position + glm::vec3(0.0f, 1.0f, 0.0f), 0.5f, WHITE_MATERIAL);
    std::array<PointLight, 1> point_lights{ point_light };

    // UNIFORMS -------------------------------------------------------------------------------------------------------------------------------------

    glm::mat4 view;
    glm::mat4 projection = glm::perspective(static_cast<double>(camera.fov_radians), ASPECT_RATIO, CAMERA_NEAR, CAMERA_FAR);
    for (const std::shared_ptr<Shader>& shader : shaders) {
        shader->set_uniform("ambient_light", ambient_light.intensity);
        shader->set_uniform("projection", projection);

        for (int i = 0; i < point_lights.size(); i++) {
            std::string uniform = "lights[" + std::to_string(i) + "].intensity";
            shader->set_uniform(uniform.c_str(), point_lights[i].intensity);
        }
    }

    // FBO -------------------------------------------------------------------------------------------------------------------------------------

    FBO fbo(SCREEN_WIDTH, SCREEN_HEIGHT);

    // quad to render the fbo

    GLuint quad_vao;
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);

    static const GLfloat quad_data[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f
    };

    GLuint quad_vbo;
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    quad_shader->set_uniform("texture_id", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo.g_position);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbo.g_normal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, fbo.g_diffuse);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, fbo.g_specular);

    // MAIN LOOP ------------------------------------------------------------------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        current_frame_time = static_cast<float>(glfwGetTime());
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
        
        move_camera();
        view = glm::lookAt(camera.transform.position, camera.transform.position + camera.front, world_up);
        point_lights[0].position = glm::rotate(rectangle.transform.position + glm::vec3(0.0f, 1.0f, 0.0f), static_cast<float>(PI * 2 / 5.0 * glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));

        for (const std::shared_ptr<Shader>& shader : shaders) {
            shader->set_uniform("view", view);
            shader->set_uniform("camera_pos", camera.transform.position);

            for (int i = 0; i < point_lights.size(); i++) {
                std::string uniform = "lights[" + std::to_string(i) + "].position";
                shader->set_uniform(uniform.c_str(), point_lights[i].position);
            }
        }

        glEnable(GL_DEPTH_TEST);
        fbo.bind();
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer::draw(cylinder);
        Renderer::draw(rectangle);
        Renderer::draw(rectangle1);
        fbo.unbind();

        glDisable(GL_DEPTH_TEST);
        quad_shader->use();
        glBindVertexArray(quad_vao);
        glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
    glDisable(GL_BLEND);

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
