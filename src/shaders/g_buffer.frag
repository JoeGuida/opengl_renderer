#version 330 core

struct Material {
	vec3 diffuse;
	vec3 specular;
	float alpha;
};
uniform Material material;

layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normal;
layout (location = 2) out vec3 g_diffuse;
layout (location = 3) out vec4 g_specular; // w component is alpha

in vec3 frag_pos;
in vec3 normal;
in vec3 tex_coords;

void main() {
	g_position = frag_pos;
	g_normal = normal;
	g_diffuse = material.diffuse;
	g_specular = vec4(material.specular.xyz, material.alpha);
};