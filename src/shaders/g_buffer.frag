#version 330 core

layout(location = 0) out vec4 g_position;
layout(location = 1) out vec3 g_normal;
layout(location = 2) out vec3 g_diffuse;
layout(location = 3) out vec4 g_specular;

struct Material {
	vec3 diffuse;
	vec3 specular;
	float alpha;
};
uniform Material material;

in vec4 position;
in vec3 normal;

void main() {
    g_position = position;
    g_normal = normal;
    g_diffuse = material.diffuse;
    g_specular = vec4(material.specular, material.alpha);
};