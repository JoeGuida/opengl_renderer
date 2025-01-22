#ifndef OPENGL_RENDERER_SHAPE_HPP
#define OPENGL_RENDERER_SHAPE_HPP

#include <utility>

enum class PrimitiveShape {
	CYLINDER,
	ICOSAHEDRON,
	MESH,
	OCTAHEDRON,
	RECTANGLE,
	SPHERE,
	TETRAHEDRON,
	TRIANGLE
};

template <std::size_t S>
class Shape {
public:
	virtual std::array<uint32_t, S> get_indices() const = 0;
	virtual std::array<float, S>  get_vertices() const = 0;
	virtual PrimitiveShape get_shape() const = 0;
};

#endif