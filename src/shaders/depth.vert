#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in float camera_near;
in float camera_far;

out vec3 frag_pos;
out vec3 vertex_normal;
out vec4 p;
out float near;
out float far;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    frag_pos = vec3(model * vec4(pos, 1.0));
    vertex_normal = normal;
    p = projection * view * model * vec4(pos, 1.0);
}