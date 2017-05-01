#version 400 core

#include <standard.glinc>

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpec;

uniform vec3 viewPos;

void main(void){
    vec3 FragPos = texture(gPosition, TexCoord).rgb;
    vec3 Normal = texture(gNormal, TexCoord).rgb;
    vec3 Color = texture(gColorSpec, TexCoord).rgb;
    float specular = texture(gColorSpec, TexCoord).a;

    vec3 lighting = Color * 0.3;
    vec3 viewDir = normalize(viewPos - FragPos);
    for(int i = 0; i < LightCount; i++){
        vec3 lightDir = normalize(Light[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Color * Light[i].Color;
        lighting += diffuse;
    }

    color = vec4(lighting, 1.0);
}