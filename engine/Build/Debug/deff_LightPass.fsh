#version 400 core

#include <standard.glinc>
#include <PBR.glinc>
#include <shadow.glinc>

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpec;
uniform sampler2D gTangent;
uniform sampler2D gFPLS;

uniform sampler2DArray shadowArray;

uniform vec3 viewPos;

void main(void){
    vec3 FragPos = texture(gPosition, TexCoord).rgb;
    vec3 Normal = texture(gNormal, TexCoord).rgb;
    vec3 Tangent = texture(gTangent, TexCoord).rgb;
    vec4 FPLS = texture(gFPLS, TexCoord);
    vec3 Color = texture(gColorSpec, TexCoord).rgb;
    float specular = texture(gColorSpec, TexCoord).a;
    vec3 B = cross(Tangent, Normal);
    mat3 TBN = mat3(Tangent, B, Normal);

    _GlobalAmbient = texture(_WorldCubeMap,vec3(1,0,0),12).rgb+texture(_WorldCubeMap,vec3(-1,0,0),12).rgb+texture(_WorldCubeMap,vec3(0,1,0),12).rgb

    +texture(_WorldCubeMap,vec3(0,-1,0),12).rgb+texture(_WorldCubeMap,vec3(0,0,1),12).rgb+texture(_WorldCubeMap,vec3(0,0,-1),12).rgb;
    _GlobalAmbient/=6;

    vec3 lighting = Color * 0.1;
    vec3 viewDir = normalize(viewPos - FragPos);
    for(int i = 0; i < LightCount; i++){
        float bias = max(0.05 * (1.0 - dot(Normal, (Light[i].Position - FragPos))), 0.005);
        vec3 lightDir = normalize(Light[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Color * Light[i].Color;
        float shadow = calculateShadow(FPLS, shadowArray, Light[i].ShadowIndex, bias);
        lighting += (1.0-shadow) * diffuse;
    }

    color = vec4(lighting, 1.0);
}