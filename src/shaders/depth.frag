#version 330 core

uniform vec3 color;
uniform float ambient;
uniform vec3 light_pos;
uniform float light_intensity;
uniform vec3 camera_position;

in vec3 frag_pos;
in vec3 vertex_normal;
in vec4 p;

in float near;
in float far;

out vec4 frag_color;

float linearize_depth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
    float depth = linearize_depth(gl_FragCoord.z);
    frag_color = vec4(vec3(depth), 1.0);
};