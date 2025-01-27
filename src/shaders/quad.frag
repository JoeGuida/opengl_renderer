#version 330 core

in vec2 uv;

layout (location = 0) out vec4 color;

uniform sampler2D rendered_texture;

void main(){
    color = vec4(texture(rendered_texture, uv).xyz, 1.0);
}