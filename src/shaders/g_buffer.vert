#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texture_coordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 position;
out vec3 normal;
out vec2 texture_coordinates;

void main() {
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
    position = vec4(model * vec4(vertex_position, 1.0));
    normal = abs(vertex_normal);
    texture_coordinates = vertex_texture_coordinates;
}