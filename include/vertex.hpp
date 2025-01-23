#ifndef OPENGL_RENDERER_VERTEX_HPP
#define OPENGL_RENDERER_VERTEX_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;

	Vertex() : position(glm::vec3(0.0f)), normal(glm::vec3(0.0f)), tex_coords(glm::vec3(0.0f)) {}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& tex_coords) : 
		position(position), normal(normal), tex_coords(tex_coords) {}
};

#endif