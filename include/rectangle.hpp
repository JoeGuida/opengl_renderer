#ifndef OPENGL_RENDERER_RECTANGLE_HPP
#define OPENGL_RENDERER_RECTANGLE_HPP

#include "glm/vec3.hpp"

#include "material.hpp"
#include "transform.hpp"

#include <array>
#include <iostream>

class Rectangle {
private:
    glm::vec2 size;
    std::array<uint32_t, 36> indices;
    std::array<Vertex, 24> vertices;

public:
    BRDFMaterial material;
    Transform transform;

    Rectangle(const glm::vec3& size, const BRDFMaterial& material, const Transform& transform) :
        size(size), material(material), transform(transform) {
        glm::vec3 half_size = size / 2.0f;

        vertices = {
            // FRONT
            Vertex(glm::vec3(-half_size.x,  half_size.y, -half_size.z), glm::vec3(0.0f, 0.0f, -1.0f)),
            Vertex(glm::vec3(half_size.x,  half_size.y, -half_size.z),  glm::vec3(0.0f, 0.0f, -1.0f)),
            Vertex(glm::vec3(-half_size.x, -half_size.y, -half_size.z), glm::vec3(0.0f, 0.0f, -1.0f)),
            Vertex(glm::vec3(half_size.x, -half_size.y, -half_size.z),  glm::vec3(0.0f, 0.0f, -1.0f)),

            // RIGHT
            Vertex(glm::vec3(half_size.x,  half_size.y, -half_size.z), glm::vec3(1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x,  half_size.y,  half_size.z), glm::vec3(1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x, -half_size.y, -half_size.z), glm::vec3(1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x, -half_size.y,  half_size.z), glm::vec3(1.0f, 0.0f, 0.0f)),

            // BACK
            Vertex(glm::vec3(half_size.x,  half_size.y, half_size.z),  glm::vec3(0.0f, 0.0f, 1.0f)),
            Vertex(glm::vec3(-half_size.x,  half_size.y, half_size.z), glm::vec3(0.0f, 0.0f, 1.0f)),
            Vertex(glm::vec3(half_size.x, -half_size.y, half_size.z),  glm::vec3(0.0f, 0.0f, 1.0f)),
            Vertex(glm::vec3(-half_size.x, -half_size.y, half_size.z), glm::vec3(0.0f, 0.0f, 1.0f)),

            // LEFT
            Vertex(glm::vec3(-half_size.x,  half_size.y,  half_size.z), glm::vec3(-1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(-half_size.x,  half_size.y, -half_size.z), glm::vec3(-1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(-half_size.x, -half_size.y,  half_size.z), glm::vec3(-1.0f, 0.0f, 0.0f)),
            Vertex(glm::vec3(-half_size.x, -half_size.y, -half_size.z), glm::vec3(-1.0f, 0.0f, 0.0f)),

            // TOP
            Vertex(glm::vec3(-half_size.x,  half_size.y,  half_size.z), glm::vec3(0.0f, 1.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x,  half_size.y,  half_size.z),  glm::vec3(0.0f, 1.0f, 0.0f)),
            Vertex(glm::vec3(-half_size.x,  half_size.y, -half_size.z), glm::vec3(0.0f, 1.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x,  half_size.y, -half_size.z),  glm::vec3(0.0f, 1.0f, 0.0f)),

            // BOTTOM
            Vertex(glm::vec3(-half_size.x, -half_size.y, -half_size.z), glm::vec3(0.0f, -1.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x, -half_size.y, -half_size.z),  glm::vec3(0.0f, -1.0f, 0.0f)),
            Vertex(glm::vec3(-half_size.x, -half_size.y,  half_size.z), glm::vec3(0.0f, -1.0f, 0.0f)),
            Vertex(glm::vec3(half_size.x, -half_size.y,  half_size.z),  glm::vec3(0.0f, -1.0f, 0.0f))
        };

        indices = {
             0,  1,  2,  1,  2,  3,
             4,  5,  6,  5,  6,  7,
             8,  9, 10,  9, 10, 11,
            12, 13, 14, 13, 14, 15,
            16, 17, 18, 17, 18, 19,
            20, 21, 22, 21, 22, 23
        };
    }

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    virtual ~Rectangle() = default;

    std::array<uint32_t, 36> get_indices() const { return indices; }
    std::array<Vertex, 24> get_vertices() const { return vertices; }
};

#endif