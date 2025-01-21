#ifndef OPENGL_RENDERER_LIGHT_HPP
#define OPENGL_RENDERER_LIGHT_HPP

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

struct AmbientLight {
	float intensity;

	AmbientLight(float intensity) : intensity(intensity) {}
};

struct DirectionalLight {
	glm::vec3 direction;
	float intensity;

	DirectionalLight(const glm::vec3& direction, float intensity) :
		direction(glm::normalize(direction)), intensity(intensity) {}
};

struct PointLight {
	glm::vec3 position;
	float intensity;

	PointLight(const glm::vec3 position, float intensity) : 
		position(position), intensity(intensity) {}
};

#endif