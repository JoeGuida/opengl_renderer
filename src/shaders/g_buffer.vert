#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 frag_pos;
out vec3 vertex_normal;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    frag_pos = vec4(model * vec4(pos, 1.0));
    vertex_normal = normal;
}