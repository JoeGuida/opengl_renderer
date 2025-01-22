#ifndef OPENGL_RENDERER_VERTEX_HPP
#define OPENGL_RENDERER_VERTEX_HPP

#include "glm/vec3.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;

	Vertex() : position(glm::vec3(0.0f)), normal(glm::vec3(0.0f)) {}
	Vertex(const glm::vec3& position, const glm::vec3& normal) : position(position), normal(normal) {}
};

#endif