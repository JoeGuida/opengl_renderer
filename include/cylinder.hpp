#ifndef OPENGL_RENDERER_CYLINDER_HPP
#define OPENGL_RENDERER_CYLINDER_HPP
#define GLM_ENABLE_EXPERIMENTAL

#define PI 3.14159265358979323846

#include "glm/vec3.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "material.hpp"
#include "transform.hpp"

class Cylinder {
private:
	int segments;
	std::vector<glm::vec3> vertices;
	std::vector<uint32_t> indices;
	
public:
	float radius;
	float height;
	BRDFMaterial material;
	Transform transform;

	Cylinder(float radius, float height, int segments, const BRDFMaterial& material, const Transform& transform):
		radius(radius), height(height), segments(segments), material(material), transform(transform)
	{
		glm::vec3 bottom_center = glm::vec3(0.0f, (-height / 2.0f), 0.0f);
		glm::vec3 top_center = glm::vec3(0.0f, (height / 2.0f), 0.0f);
		float angle = 2 * PI / (segments - 1);

		// bottom circle
		vertices.push_back(bottom_center);
		for (int i = 0; i < segments - 1; i++) {
			vertices.push_back(glm::rotateY(bottom_center + glm::vec3(radius, 0.0f, 0.0f), angle * i));
		}
		for (int i = 1; i < vertices.size() - 1; i++) {
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		indices.push_back(0);
		indices.push_back(indices[indices.size() - 2]);
		indices.push_back(1);
		int n = vertices.size();

		// top circle
		vertices.push_back(top_center);
		int s = indices[indices.size() - 2] + 1;
		for (int i = 0; i < segments - 1; i++) {
			vertices.push_back(glm::rotateY(top_center + glm::vec3(radius, 0.0f, 0.0f), angle * i));
		}
		for (int i = n; i < vertices.size() - 1; i++) {
			indices.push_back(s);
			indices.push_back(s + (i - n));
			indices.push_back(s + (i - n) + 1);
		}
		indices.push_back(s);
		indices.push_back(indices[indices.size() - 2]);
		indices.push_back(s + 1);

		// sides
		int idx = 1;
		for (int i = 0; i < segments - 2; i++) {
			glm::vec v = vertices[1 + idx];
			indices.push_back(idx);
			indices.push_back(idx + segments);
			indices.push_back(idx + segments + 1);
			indices.push_back(idx);
			indices.push_back(idx + 1);
			indices.push_back(idx + segments + 1);
			idx++;
		}

		indices.push_back(segments - 1);
		indices.push_back(segments * 2 - 1);
		indices.push_back(segments + 1);

		indices.push_back(segments - 1);
		indices.push_back(1);
		indices.push_back(segments + 1);
	}

	std::vector<glm::vec3> get_vertices() const { return vertices; }
	std::vector<uint32_t> get_indices() const { return indices; }
};

#endif