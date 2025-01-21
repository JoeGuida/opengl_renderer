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
    std::array<uint32_t, 108> indices;
    std::array<float, 144> vertices;

public:
    BRDFMaterial material;
    Transform transform;

    Rectangle(const glm::vec3& size, const BRDFMaterial& material, const Transform& transform) :
        size(size), material(material), transform(transform) {
        glm::vec3 half_size = size / 2.0f;

        vertices = {
            -half_size.x,  half_size.y,  half_size.z, 0.0f, 0.0f, -1.0f,
             half_size.x,  half_size.y,  half_size.z, 0.0f, 0.0f, -1.0f,
            -half_size.x, -half_size.y,  half_size.z, 0.0f, 0.0f, -1.0f,
             half_size.x, -half_size.y,  half_size.z, 0.0f, 0.0f, -1.0f,
            -half_size.x,  half_size.y, -half_size.z, 0.0f, 0.0f,  1.0f,
             half_size.x,  half_size.y, -half_size.z, 0.0f, 0.0f,  1.0f,
            -half_size.x, -half_size.y, -half_size.z, 0.0f, 0.0f,  1.0f,
             half_size.x, -half_size.y, -half_size.z, 0.0f, 0.0f,  1.0f,

            -half_size.x,  half_size.y,  half_size.z, -1.0f, 0.0f, 0.0f,
             half_size.x,  half_size.y,  half_size.z,  1.0f, 0.0f, 0.0f,
            -half_size.x, -half_size.y,  half_size.z, -1.0f, 0.0f, 0.0f,
             half_size.x, -half_size.y,  half_size.z,  1.0f, 0.0f, 0.0f,
            -half_size.x,  half_size.y, -half_size.z, -1.0f, 0.0f, 0.0f,
             half_size.x,  half_size.y, -half_size.z,  1.0f, 0.0f, 0.0f,
            -half_size.x, -half_size.y, -half_size.z, -1.0f, 0.0f, 0.0f,
             half_size.x, -half_size.y, -half_size.z,  1.0f, 0.0f, 0.0f,

            -half_size.x,  half_size.y,  half_size.z, 0.0f,  1.0f, 0.0f,
             half_size.x,  half_size.y,  half_size.z, 0.0f,  1.0f, 0.0f,
            -half_size.x, -half_size.y,  half_size.z, 0.0f, -1.0f, 0.0f,
             half_size.x, -half_size.y,  half_size.z, 0.0f, -1.0f, 0.0f,
            -half_size.x,  half_size.y, -half_size.z, 0.0f,  1.0f, 0.0f,
             half_size.x,  half_size.y, -half_size.z, 0.0f,  1.0f, 0.0f,
            -half_size.x, -half_size.y, -half_size.z, 0.0f, -1.0f, 0.0f,
             half_size.x, -half_size.y, -half_size.z, 0.0f, -1.0f, 0.0f
        };

        indices = {
            0, 1, 3, 0, 2, 3,
            1, 5, 7, 1, 3, 7,
            4, 5, 7, 4, 6, 7,
            4, 0, 6, 0, 6, 2,
            4, 5, 1, 4, 0, 1,
            2, 3, 6, 3, 6, 7,

            8, 9, 11, 8, 10, 11,
            9, 13, 15, 9, 11, 15,
            12, 13, 15, 12, 14, 15,
            12, 8, 14, 8, 14, 10,
            12, 13, 9, 12, 8, 9,
            10, 11, 14, 11, 14, 15,

            16, 17, 19, 16, 18, 19,
            17, 21, 23, 17, 19, 23,
            20, 21, 23, 20, 22, 23,
            20, 16, 22, 16, 22, 18,
            20, 21, 17, 20, 16, 17,
            18, 19, 22, 19, 22, 23
        };
    }

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    virtual ~Rectangle() = default;

    std::array<uint32_t, 108> get_indices() const { return indices; }
    std::array<float, 144> get_vertices() const { return vertices; }
};

#endif