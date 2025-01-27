#ifndef OPENGL_RENDERER_MATERIAL_HPP
#define OPENGL_RENDERER_MATERIAL_HPP

#include "glm/vec3.hpp"

#include "shader.hpp"

struct Material {
	virtual bool is_light() const = 0;
};

struct BRDFMaterial : Material {
	std::shared_ptr<Shader> shader;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float alpha;
	uint32_t specularity;

	BRDFMaterial() : shader(shader), diffuse(glm::vec3(0.0f)), specular(glm::vec3(0.0f)), alpha(0.0f), specularity(0) {}
	BRDFMaterial(std::shared_ptr<Shader> shader, const glm::vec3& diffuse, const glm::vec3& specular, float alpha, uint32_t specularity) : shader(shader), diffuse(diffuse), specular(specular), alpha(alpha), specularity(specularity) {}

	BRDFMaterial(const BRDFMaterial&) = default;
	BRDFMaterial(BRDFMaterial&&) = default;
	virtual ~BRDFMaterial() = default;

	bool is_light() const override { return false; }
};

struct LightMaterial : Material {
	std::shared_ptr<Shader> shader;
	glm::vec3 color;

	LightMaterial() : shader(shader), color(glm::vec3(0.0f)) {}
	LightMaterial(std::shared_ptr<Shader> shader, const glm::vec3& color) : shader(shader), color(color) {}

	LightMaterial(const LightMaterial&) = default;
	LightMaterial(LightMaterial&&) = default;
	virtual ~LightMaterial() = default;

	bool is_light() const override { return true; }
};

#endif