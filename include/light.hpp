#ifndef OPENGL_RENDERER_LIGHT_HPP
#define OPENGL_RENDERER_LIGHT_HPP

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

#include "material.hpp"

struct AmbientLight {
	float intensity;

	AmbientLight(float intensity) : intensity(intensity) {}

	AmbientLight(const AmbientLight&) = default;
	AmbientLight(AmbientLight&&) = default;
	virtual ~AmbientLight() = default;
};

struct DirectionalLight {
	glm::vec3 direction;
	float intensity;

	DirectionalLight(const glm::vec3& direction, float intensity) :
		direction(glm::normalize(direction)), intensity(intensity) {}

	DirectionalLight(const DirectionalLight&) = default;
	DirectionalLight(DirectionalLight&&) = default;
	virtual ~DirectionalLight() = default;
};

struct PointLight {
	glm::vec3 position;
	float intensity;
	BRDFMaterial material;

	PointLight(const glm::vec3 position, float intensity, const BRDFMaterial& material) : 
		position(position), intensity(intensity), material(material) {}

	PointLight(const PointLight&) = default;
	PointLight(PointLight&&) = default;
	virtual ~PointLight() = default;
};

#endif