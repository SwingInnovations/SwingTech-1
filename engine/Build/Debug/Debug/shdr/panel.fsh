#version 400 core

in vec2 TexCoord;

uniform vec4 baseColor;

out vec4 Frag;

void main(void){
    Frag = vec4(baseColor);;
}