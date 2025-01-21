#version 330 core

uniform vec3 color;
uniform float ambient;
uniform vec3 light_pos;
uniform float light_intensity;

in vec3 frag_pos;
in vec3 vertex_normal;

out vec4 frag_color;

void main() {
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diffuse = max(dot(vertex_normal, -light_dir) * light_intensity, 0.0);
    frag_color = vec4((ambient + diffuse) * color, 1.0);
};