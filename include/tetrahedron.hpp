#ifndef OPENGL_RENDERER_TETRAHEDRON_HPP
#define OPENGL_RENDERER_TETRAHEDRON_HPP

#include "material.hpp"
#include "transform.hpp"

#include <array>

class Tetrahedron {
private:
	std::array<uint32_t, 12> indices;
	std::array<Vertex, 4> vertices;
	float size;

public:
	BRDFMaterial material;
	Transform transform;

	Tetrahedron(float size, const BRDFMaterial& material, const Transform& transform) : 
		size(size), material(material), transform(transform) {
		float half_size = size / 2.0f;

		vertices = {
			Vertex(glm::vec3(-half_size, -half_size, half_size), glm::vec3(0.0f, -1.0f, 0.0f)),
			Vertex(glm::vec3(half_size, -half_size, half_size), glm::vec3(0.0f, -1.0f, 0.0f)),
			Vertex(glm::vec3(0.0f, -half_size, -half_size), glm::vec3(0.0f, -1.0f, 0.0f)),
			Vertex(glm::vec3(0.0f,  half_size, half_size), glm::vec3(0.0f, 1.0f, 0.0f))
		};

		indices = {
			0, 1, 2,
			0, 3, 1,
			1, 3, 2,
			2, 3, 0
		};
	}

	Tetrahedron(const Tetrahedron&) = default;
	Tetrahedron(Tetrahedron&&) = default;
	virtual ~Tetrahedron() = default;

	std::array<uint32_t, 12> get_indices() const { return indices; }
	std::array<Vertex, 4> get_vertices() const { return vertices; }
};

#endif