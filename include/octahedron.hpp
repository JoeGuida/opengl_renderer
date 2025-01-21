#ifndef OPENGL_RENDERER_OCTAHEDRON_HPP
#define OPENGL_RENDERER_OCTAHEDRON_HPP

#include "material.hpp"
#include "transform.hpp"

#include <array>

class Octahedron {
private:
	std::array<uint32_t, 24> indices;
	std::array<float, 36> vertices;
	float size;

public:
	BRDFMaterial material;
	Transform transform;

	Octahedron(float size, const BRDFMaterial& material, const Transform& transform) :
		size(size), material(material), transform(transform) {
		float s = size / 2.0f;

		vertices = {
			-s, 0.0f, -s,    0.0f, 0.0f, 0.0f,
			 s, 0.0f, -s,    0.0f, 0.0f, 0.0f,
			-s, 0.0f,  s,    0.0f, 0.0f, 0.0f,
			 s, 0.0f,  s,    0.0f, 0.0f, 0.0f,
		     0.0f, s, 0.0f,  0.0f, 0.0f, 0.0f,
			 0.0f, -s, 0.0f, 0.0f, 0.0f, 0.0f
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

	std::array<uint32_t, 24> get_indices() const { return indices; }
	std::array<float, 36> get_vertices() const { return vertices; }
};

#endif