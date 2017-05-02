#version 400 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gColorSpec;
layout(location = 3) out vec3 gTangent;
layout(location = 4) out vec4 gFPLS;

#include <standard.glinc>
in vec4 FragPosLightSpace;

uniform sampler2D texture_specular;

void main(void){
    gPosition = Position;
    gNormal = normalize(Normal);
    gTangent = normalize(Tangent);
    gColorSpec.rgb = texture(Material.Diffuse_Tex, TexCoord).rgb;
    gColorSpec.a = texture(texture_specular, TexCoord).r;
    gFPLS = FragPosLightSpace;
}