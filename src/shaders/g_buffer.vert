#version 330 core

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 frag_pos;
out vec3 normal;
out vec2 tex_coords;

void main() {
    gl_Position = projection * view * model * vec4(vertex_pos, 1.0);
    frag_pos = vec3(model * vec4(vertex_pos, 1.0));
    normal = vertex_normal;
    tex_coords = vertex_tex_coords;
}