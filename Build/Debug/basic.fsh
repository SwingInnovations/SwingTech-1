#version 330 core

in vec3 position0;
in vec2 texCoord0;

uniform float uniR;
uniform float uniG;
uniform float uniB;

out vec4 color;

void main(void){
    color = vec4(clamp(uniR, 0.0, 1.0), clamp(uniG, 0.0, 1.0), clamp(uniB, 0.0, 1.0), 1.0);
}
