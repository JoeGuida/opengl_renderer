#include "mesh.hpp"

void Mesh::load_from_file(const std::string& filename, bool flip_yz_axis) {
	std::string line;
	std::ifstream file(filename);
	std::vector<std::vector<std::string>> all_items;
	while (std::getline(file, line)) {
		line += ' ';
		std::string item;
		std::vector<std::string> items;

		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ' ' && item.length() >= 1) {
				items.push_back(item);
				item = "";
			}
			else {
				item += line[i];
			}
		}

		all_items.push_back(items);
	}

	for (int i = 0; i < all_items.size(); i++) {
		if (all_items[i].size() == 0) {
			continue;
		}
		execute_command(OBJ_COMMANDS[all_items[i][0]], all_items[i]);
	}

	// flip y and z axis of vertices
	if (flip_yz_axis) {
		for (int i = 0; i < vertices.size(); i += 6) {
			float temp = vertices[i + 1];
			vertices[i + 1] = vertices[i + 2];
			vertices[i + 2] = temp;
		}
	}
}

void Mesh::execute_command(const OBJ_COMMAND& command, std::vector<std::string>& items) {
	if (command == OBJ_COMMAND::OBJ_VERTEX) {
		add_vertex(items, 6);
	}

	if (command == OBJ_COMMAND::OBJ_FACE) {
		add_face(items);
	}
}

void Mesh::add_vertex(const std::vector<std::string>& items, float stride) {
	if (items.size() != 4) {
		return;
	}

	std::array<float, 3> vertex;
	for (int i = 1; i < items.size(); i++) {
		vertex[i - 1] = std::stof(items[i]);
	}

	for (int i = 0; i < vertex.size(); i++) {
		vertices.push_back(vertex[i]);
	}
	for (int i = 0; i < stride - vertex.size(); i++) {
		vertices.push_back(0.0f);
	}
}

void Mesh::add_face(std::vector<std::string>& items) {
	if (items[1].find('/') == -1) {
		for (int i = 1; i < items.size(); i++) {
			indices.push_back(std::stoi(items[i]) - 1);
		}
	}
	if (items[1].find('/') != -1) {
		// remove '/' from faces and replace with ' '
		std::vector<std::string> parsed_indices;
		for (int i = 0; i < items.size(); i++) {
			for (int j = 0; j < items[i].length(); j++) {
				std::string str = items[i];
				char c = items[i][j];
				if (c == '/') {
					str.replace(j, 1, " ");
					items[i] = str;
				}
			}
			items[i] += ' ';
		}

		// put all indices into parsed_indices
		for (int i = 1; i < items.size(); i++) {
			std::string item;
			for (int j = 0; j < items[i].length(); j++) {
				if (items[i][j] == ' ') {
					indices.push_back(std::stoi(item) - 1);
					item = "";
				}
				else {
					item += items[i][j];
				}
			}
		}
	}
}