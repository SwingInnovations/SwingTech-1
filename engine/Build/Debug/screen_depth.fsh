#version 400 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D depthMap;

void main(void){
    float value = texture(depthMap, TexCoord).r;
    color = vec4(vec3(value), 1.0);
}