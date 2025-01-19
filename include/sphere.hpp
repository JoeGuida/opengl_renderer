#ifndef OPENGL_RENDERER_SPHERE_HPP
#define OPENGL_RENDERER_SPHERE_HPP

#include "glm/vec3.hpp"

#include "material.hpp"
#include "transform.hpp"

struct Sphere {
	float radius;
	int depth;
	BRDFMaterial material;
	Transform transform;

	Sphere(float radius, int depth, const BRDFMaterial& material, const Transform& transform) : 
		radius(radius), depth(depth), material(material), transform(transform) {}
};

#endif