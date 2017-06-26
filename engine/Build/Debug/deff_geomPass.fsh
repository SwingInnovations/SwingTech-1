#version 400 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gColorSpec;
layout(location = 3) out vec3 gNormalMap;
layout(location = 4) out vec3 gMRA;
layout(location = 5) out vec3 gTangent;

#include <standard.glinc>

uniform sampler2D texture_specular;
uniform sampler2D texture_Metallic;
uniform sampler2D texture_Roughness;
uniform sampler2D texture_AmbientOcclusion;

void main(void){
    vec3 B = cross(Tangent, Normal);
    mat3 TBN = mat3(Tangent, B, Normal);
    gPosition = Position;
    if(Material.Normal_Use == 0) gNormal = mix(Normal, normalize(TBN * normalize(texture2D(Material.Normal_Tex, TexCoord).rgb*2.0 - 1.0)), 0.1);
    else gNormal = normalize(Normal);
    gTangent = normalize(Tangent);
    gColorSpec.rgb = ColorEval3x4(texture(Material.Diffuse_Tex, TexCoord).rgb, Material.Diffuse_Color);
    gColorSpec.a = texture(texture_specular, TexCoord).r;
    gNormalMap = (Material.Normal_Use == 1) ? texture(Material.Normal_Tex, TexCoord).rgb : vec3(0.0);
    gMRA.r = Material.Metallic.x;
    gMRA.g = Material.Roughness.x;
}