#version 330 core

uniform vec3 color;

in vec3 frag_pos;
in vec3 vertex_normal;

out vec4 frag_color;

void main() {
    frag_color = vec4(color, 1.0);
};