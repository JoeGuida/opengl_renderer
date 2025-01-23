#ifndef OPENGL_RENDERER_CYLINDER_HPP
#define OPENGL_RENDERER_CYLINDER_HPP
#define GLM_ENABLE_EXPERIMENTAL

#define PI 3.14159265358979323846

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "material.hpp"
#include "shape.hpp"
#include "transform.hpp"
#include "vertex.hpp"

class Cylinder {
private:
	int segments;
	std::vector<Vertex> vertices;
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
		vertices.push_back(Vertex(bottom_center, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
		for (int i = 0; i < segments - 1; i++) {
			glm::vec3 v = glm::rotateY(bottom_center + glm::vec3(radius, 0.0f, 0.0f), angle * i);
			vertices.push_back(Vertex(v, glm::vec3(v.x, 0.0f, v.z), glm::vec2(0.0f, 0.0f)));
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
		vertices.push_back(Vertex(top_center, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
		int s = indices[indices.size() - 2] + 1;
		for (int i = 0; i < segments - 1; i++) {
			glm::vec3 v = glm::rotateY(top_center + glm::vec3(radius, 0.0f, 0.0f), angle * i);
			vertices.push_back(Vertex(v, glm::vec3(v.x, 0.0f, v.z), glm::vec2(0.0f, 0.0f)));
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

		int size = vertices.size();
		for (int i = 0; i < size; i++) {
			if (i < vertices.size() / 2) {
				Vertex v = vertices[i];
				v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
				vertices.push_back(v);
			}
			else {
				Vertex v = vertices[i];
				v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
				vertices.push_back(v);
			}
		}
	}

	Cylinder(const Cylinder&) = default;
	Cylinder(Cylinder&&) = default;
	virtual ~Cylinder() = default;

	std::vector<Vertex> get_vertices() const { return vertices; }
	std::vector<uint32_t> get_indices() const { return indices; }
};

#endif