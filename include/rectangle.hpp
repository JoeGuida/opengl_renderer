#ifndef OPENGL_RENDERER_RECTANGLE_HPP
#define OPENGL_RENDERER_RECTANGLE_HPP

#include "glm/vec3.hpp"

#include "material.hpp"
#include "transform.hpp"

#include <array>

class Rectangle {
private:
    glm::vec2 size;
    std::array<uint32_t, 36> indices;
    std::array<float, 24> vertices;

public:
    BRDFMaterial material;
    Transform transform;

    Rectangle(const glm::vec3& size, const BRDFMaterial& material, const Transform& transform) :
        size(size), material(material), transform(transform) {
        glm::vec3 half_size = size / 2.0f;

        vertices = {
            -half_size.x,  half_size.y,  half_size.z,
             half_size.x,  half_size.y,  half_size.z,
            -half_size.x, -half_size.y,  half_size.z,
             half_size.x, -half_size.y,  half_size.z,
            -half_size.x,  half_size.y, -half_size.z,
             half_size.x,  half_size.y, -half_size.z,
            -half_size.x, -half_size.y, -half_size.z,
             half_size.x, -half_size.y, -half_size.z,
        };

        indices = {
            0, 1, 3, 0, 2, 3,
            1, 5, 7, 1, 3, 7,
            4, 5, 7, 4, 6, 7,
            4, 0, 6, 0, 6, 2,
            4, 5, 1, 4, 0, 1,
            2, 3, 6, 3, 6, 7
        };
    }

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    virtual ~Rectangle() = default;

    std::array<uint32_t, 36> get_indices() const { return indices; }
    std::array<float, 24> get_vertices() const { return vertices; }
};

#endif