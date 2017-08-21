#version 400 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D depthMap;

void main(void){
    vec2 tex = vec2(TexCoord.x, 1.0 - TexCoord.y);
    float value = texture(depthMap, tex).r;
    color = vec4(vec3(value), 1.0);
}