#version 400 core

in vec2 TexCoord;
uniform sampler2D ShadowImage;

out vec4 Color;

void main(void){
    float depthValue = texture2D(ShadowImage, TexCoord).r;
    Color = vec4(vec3(depthValue), 1.0);
}