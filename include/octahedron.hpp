#ifndef OPENGL_RENDERER_OCTAHEDRON_HPP
#define OPENGL_RENDERER_OCTAHEDRON_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "material.hpp"
#include "transform.hpp"
#include "vertex.hpp"

#include <array>

class Octahedron {
private:
	std::array<uint32_t, 24> indices;
	std::array<Vertex, 6> vertices;
	float size;

public:
	BRDFMaterial material;
	Transform transform;

	Octahedron(float size, const BRDFMaterial& material, const Transform& transform) :
		size(size), material(material), transform(transform) {
		float half_size = size / 2.0f;

		vertices = {
			Vertex(glm::vec3(-half_size, 0.0f, -half_size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(half_size, 0.0f, -half_size),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-half_size, 0.0f,  half_size), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(half_size, 0.0f,  half_size),  glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)),
		    Vertex(glm::vec3(0.0f, half_size, 0.0f),        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.0f, -half_size, 0.0f),       glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f))
		};

		indices = {
			0, 4, 1,
			1, 4, 3,
			0, 4, 2,
			2, 4, 3,
			0, 5, 1,
			1, 5, 3,
			0, 5, 2,
			2, 5, 3
		};
	}

	Octahedron(const Octahedron&) = default;
	Octahedron(Octahedron&&) = default;
	virtual ~Octahedron() = default;

	std::array<uint32_t, 24> get_indices() const { return indices; }
	std::array<Vertex, 6> get_vertices() const { return vertices; }
};

#endif