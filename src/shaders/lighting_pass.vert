#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormals;
layout (location = 2) in vec2 inTexCoords;

out vec2 texCoords;

void main() {
    gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0);
    texCoords = inTexCoords;
}