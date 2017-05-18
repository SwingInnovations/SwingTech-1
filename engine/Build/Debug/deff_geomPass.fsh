#version 400 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gColorSpec;
layout(location = 3) out vec3 gNormalMap;
layout(location = 4) out vec3 gMRA;
layout(location = 5) out vec3 gTangent;

#include <standard.glinc>
in vec4 FragPosLightSpace;

uniform sampler2D texture_specular;

void main(void){
    gPosition = Position;
    gNormal = normalize(Normal);
    gTangent = normalize(Tangent);
    gColorSpec.rgb = ColorEval3x4(texture(Material.Diffuse_Tex, TexCoord).rgb, Material.Diffuse_Color);
    gColorSpec.a = texture(texture_specular, TexCoord).r;
    gNormalMap = (Material.Normal_Use == 1) ? texture(Material.Normal_Tex, TexCoord).rgb : vec3(0.0);
    gMRA = vec3(0.2, 0.4, 0.0);
}