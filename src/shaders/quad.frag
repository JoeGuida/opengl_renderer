#version 330 core

in vec2 uv;

uniform sampler2D texture_id;

out vec3 color;

void main(){
    color = vec3(texture(texture_id, uv));
}