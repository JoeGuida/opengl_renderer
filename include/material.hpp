#ifndef OPENGL_RENDERER_MATERIAL_HPP
#define OPENGL_RENDERER_MATERIAL_HPP

#include "glm/vec3.hpp"

struct Material {
	virtual bool is_light() const = 0;
};

struct BRDFMaterial : Material {
	glm::vec3 diffuse;
	glm::vec3 specular;
	float alpha;
	int specularity;

	BRDFMaterial() : diffuse(glm::vec3(0.0f)), specular(glm::vec3(0.0f)), alpha(0.0f), specularity(0) {}
	BRDFMaterial(const glm::vec3& diffuse, const glm::vec3& specular, float alpha, int specularity) : diffuse(diffuse), specular(specular), alpha(alpha), specularity(specularity) {}

	BRDFMaterial(const BRDFMaterial&) = default;
	BRDFMaterial(BRDFMaterial&&) = default;
	virtual ~BRDFMaterial() = default;

	bool is_light() const override { return false; }
};

struct LightMaterial : Material {
	glm::vec3 color;

	LightMaterial() : color(glm::vec3(0.0f)) {}
	LightMaterial(const glm::vec3& color) : color(color) {}

	LightMaterial(const LightMaterial&) = default;
	LightMaterial(LightMaterial&&) = default;
	virtual ~LightMaterial() = default;

	bool is_light() const override { return true; }
};

static BRDFMaterial RED_MATERIAL(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), 0.0f, 10);
static BRDFMaterial GREEN_MATERIAL(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), 0.0f, 10);
static BRDFMaterial BLUE_MATERIAL(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), 0.0f, 10);
static BRDFMaterial YELLOW_MATERIAL(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f), 0.0f, 10);
static BRDFMaterial VIOLET_MATERIAL(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f), 0.0f, 10);
static BRDFMaterial CYAN_MATERIAL(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f), 0.0f, 10);
static BRDFMaterial WHITE_MATERIAL(glm::vec3(1.0f), glm::vec3(0.0f), 0.0f, 10);

#endif