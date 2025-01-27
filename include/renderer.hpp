#ifndef OPENGL_RENDERER_RENDERER_HPP
#define OPENGL_RENDERER_RENDERER_HPP

#include "glad/glad.h"
#include "glm/vec3.hpp"

#include "cylinder.hpp"
#include "icosahedron.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "octahedron.hpp"
#include "rectangle.hpp"
#include "shader.hpp"
#include "sphere.hpp"
#include "tetrahedron.hpp"
#include "transform.hpp"
#include "triangle.hpp"

#include <array>

class Renderer {
private:
    static uint32_t VAO;
    static uint32_t VBO;
    static uint32_t EBO;

public:
    static void initialize();
    static void draw(const Cylinder& cylinder);
    static void draw(const Icosahedron& icosahedron);
    static void draw(const Mesh& mesh);
    static void draw(const Octahedron& octahedron);
    static void draw(PointLight& point_light);
    static void draw(const Rectangle& rectangle);
    static void draw(const Sphere& sphere);
    static void draw(const Tetrahedron& tetrahedron);
    static std::vector<Triangle> subdivide_triangles(const std::vector<Triangle>& triangles, int depth);
};

#endif