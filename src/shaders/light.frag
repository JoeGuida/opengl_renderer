#version 330 core

#define NUM_LIGHTS 1

struct Material {
	vec3 diffuse;
	vec3 specular;
	float alpha;
};

struct PointLight {
    vec3 position;
    float intensity;
};

uniform PointLight lights[NUM_LIGHTS];
uniform Material material;

out vec4 frag_color;

void main() {
    frag_color = vec4(material.diffuse, 1.0);
};