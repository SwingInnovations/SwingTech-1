#version 400 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gColorSpec;

#include <standard.glinc>

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular;

void main(void){
    gPosition = Position;
    gNormal = normalize(Normal);
    gColorSpec.rgb = texture(Material.Diffuse_Tex, TexCoord).rgb;
    gColorSpec.a = texture(texture_specular, TexCoord).r;
}