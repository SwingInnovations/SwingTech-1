#version 400 core

uniform float intensity;

out vec4 color;

void main(void){
    color = vec4((intensity * vec3(1.0, 0.0, 0.0)) * vec3(1.0, 1.0, 1.0), 1.0);
}