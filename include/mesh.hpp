#ifndef OPENGL_RENDERER_MESH_HPP
#define OPENGL_RENDERER_MESH_HPP

#include "material.hpp"
#include "transform.hpp"
#include "vertex.hpp"

#include <array>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

enum class OBJ_COMMAND {
	OBJ_COMMENT,
	OBJ_VERTEX,
	OBJ_FACE,
	OBJ_NORMAL,
	OBJ_TEXTURE_COORDINATE,
	OBJ_LINE_ELEMENT,
	OBJ_MTL_FILEPATH,
	OBJ_USEMTL,
	OBJ_OBJECT_NAME,
	OBJ_GROUP_NAME,
	OBJ_SMOOTHING_GROUP
};

static std::unordered_map<std::string, OBJ_COMMAND> OBJ_COMMANDS {
	{"#",      OBJ_COMMAND::OBJ_COMMENT},
	{"v",      OBJ_COMMAND::OBJ_VERTEX},
	{"f",      OBJ_COMMAND::OBJ_FACE},
	{"vn",     OBJ_COMMAND::OBJ_NORMAL},
	{"vt",     OBJ_COMMAND::OBJ_TEXTURE_COORDINATE},
	{"l",      OBJ_COMMAND::OBJ_LINE_ELEMENT},
	{"mtllib", OBJ_COMMAND::OBJ_MTL_FILEPATH},
	{"usemtl", OBJ_COMMAND::OBJ_USEMTL},
	{"o",      OBJ_COMMAND::OBJ_OBJECT_NAME},
	{"g",      OBJ_COMMAND::OBJ_GROUP_NAME},
	{"s",      OBJ_COMMAND::OBJ_SMOOTHING_GROUP}
};

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

public:
	BRDFMaterial material;
	Transform transform;

	Mesh(const std::string& filepath, const BRDFMaterial& material, const Transform& transform) : material(material), transform(transform) { 
		load_from_file(filepath); 
	}

	Mesh(const Mesh&) = default;
	Mesh(Mesh&&) = default;
	virtual ~Mesh() = default;

	void load_from_file(const std::string& filepath, bool flip_yz_axis = false);
	void execute_command(const OBJ_COMMAND& command, std::vector<std::string>& items);
	void add_vertex(const std::vector<std::string>& items, float stride);
	void add_face(std::vector<std::string>& items);

	std::vector<uint32_t> get_indices() const { return indices; }
	std::vector<Vertex> get_vertices() const { return vertices; }
};

#endif