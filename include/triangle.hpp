#ifndef OPENGL_RENDERER_TRIANGLE_HPP
#define OPENGL_RENDERER_TRIANGLE_HPP

#include "glm/vec3.hpp"

#include <array>

struct Triangle {
	std::array<glm::vec3, 3> points;

	Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
		points[0] = a;
		points[1] = b;
		points[2] = c;
	}

	Triangle(const Triangle&) = default;
	Triangle(Triangle&&) = default;
	virtual ~Triangle() = default;

	glm::vec3 a() const { return points[0]; }
	glm::vec3 b() const { return points[1]; }
	glm::vec3 c() const { return points[2]; }
};

#endif