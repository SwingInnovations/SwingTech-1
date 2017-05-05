#version 400 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gColorSpec;
layout(location = 3) out vec3 gTangent;
layout(location = 4) out vec3 gNormalMap;
layout(location = 5) out vec3 gMRA;

#include <standard.glinc>
in vec4 FragPosLightSpace;

uniform sampler2D texture_specular;

void main(void){
    gPosition = Position;
    gNormal = normalize(Normal);
    gTangent = normalize(Tangent);
    gColorSpec.rgb = ColorEval3x4(texture(Material.Diffuse_Tex, TexCoord).rgb, Material.Diffuse_Color);
    gColorSpec.a = texture(texture_specular, TexCoord).r;
    gNormalMap = texture(Material.Normal_Tex, TexCoord).rgb;
    gMRA = vec3(0.0);
}