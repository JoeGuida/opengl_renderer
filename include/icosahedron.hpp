#ifndef OPENGL_RENDERER_ICOSAHEDRON_HPP
#define OPENGL_RENDERER_ICOSAHEDRON_HPP

#include "material.hpp"
#include "transform.hpp"

#include <array>

class Icosahedron {
private:
    std::array<uint32_t, 60> indices;
    std::array<float, 36> vertices;

public:
    float size;
    BRDFMaterial material;
	Transform transform;

	Icosahedron(float size, const Transform& transform, const BRDFMaterial& material) : size(size), transform(transform), material(material) {

        vertices = {
           -size,  size, 0.0f,
            size,  size, 0.0f,
           -size, -size, 0.0f,
            size, -size, 0.0f,

            0.0f,  size, -size,
            0.0f,  size,  size,
            0.0f, -size, -size,
            0.0f, -size,  size,

           -size, 0.0f, -size,
           -size, 0.0f,  size,
            size, 0.0f, -size,
            size, 0.0f,  size
        };

        indices = {
            0,  4,  8,
            4,  8, 10,
            1,  4, 10,
            2,  8,  6,
            8, 10,  6,
            3,  6, 10,
            0,  2,  8,
            1,  3, 10,
            0,  4,  5,
            1,  4,  5,

            1, 5, 11,
            5, 9, 11,
            0, 5,  9,
            3, 7, 11,
            7, 9, 11,
            2, 7,  9,
            1, 3, 11,
            0, 2,  9,
            6, 7,  2,
            6, 7,  3
        };
	}

    std::array<uint32_t, 60> get_indices() const { return indices; }
    std::array<float, 36> get_vertices() const { return vertices; }
};

#endif