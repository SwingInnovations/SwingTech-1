#version 400 core

in vec2 TexCoord;
in sampler2D ShadowImage

out vec4 Color;

void main(void){
    color = texture(TexCoord, ShadowImage);
}