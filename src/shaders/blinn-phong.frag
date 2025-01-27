#version 330 core

#define NUM_LIGHTS 1

struct Material {
    vec3 diffuse;
    vec3 specular;
    int specularity;
    float alpha;
};

struct PointLight {
    vec3 position;
    float intensity;
};

uniform PointLight lights[NUM_LIGHTS];
uniform Material material;
uniform vec3 camera_pos;
uniform float ambient_light;

in vec3 frag_pos;
in vec3 vertex_normal;

out vec4 frag_color;

void main() {
    float diff = 0;
    float spec = 0;
    for(int i = 0; i < NUM_LIGHTS; i++) {
        vec3 light_dir = normalize(lights[i].position - frag_pos);
        vec3 view_dir = normalize(camera_pos - frag_pos);
        vec3 h = normalize(light_dir + view_dir);
        float ndoth = dot(vertex_normal, h);
        spec += pow(max(ndoth, 0.0), 32);
        diff += max(dot(vertex_normal, light_dir) * lights[i].intensity, 0.0);
    }

    vec3 ambient = material.diffuse * ambient_light;
    vec3 diffuse = material.diffuse * min(diff, 1.0);
    vec3 specular = material.specular * min(spec, 1.0);
    frag_color = vec4(min(ambient + diffuse + specular, 1.0), 1.0);
};