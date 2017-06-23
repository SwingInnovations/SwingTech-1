#INSERT_HEADER

#include <standard.glinc>
#include <shdr/PBR.glinc>
#include <shadow.glinc>

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpec;
uniform sampler2D gNormalMap;
uniform sampler2D gMRA;
uniform sampler2D gTangent;
uniform sampler2DArray shadowArray;

void main(void){
    vec3 FragPos = texture(gPosition, TexCoord).rgb;
    vec3 Normal = texture(gNormal, TexCoord).rgb;
    vec3 Tangent = texture(gTangent, TexCoord).rgb;
    vec3 Color = texture(gColorSpec, TexCoord).rgb;
    vec3 MRA = texture(gMRA, TexCoord).rgb;
    float specular = texture(gColorSpec, TexCoord).a;
    vec3 B = cross(Tangent, Normal);
    mat3 TBN = mat3(Tangent, B, Normal);


    vec3 lighting = Color * 0.1;
    vec3 viewDir = normalize(_CameraPos - FragPos);

    for(int i = 0; i < LightCount; i++){
        float bias = max(0.05 * (1.0 - dot(Normal, (Light[i].Position - FragPos))), 0.005);
        vec4 FPLS = transpose(Light[i].LightSpaceMatrix) * vec4(FragPos, 1.0);
        float shadow = calculateShadow(FPLS, shadowArray, 0, bias);
        lighting += DirectPBR((1.0 - shadow) * Color, MRA, FragPos, Normal, Light[i].Position, Light[i].Color, _CameraPos);
    }

    color = vec4(lighting, 1.0);

    //color = vec4(FragPos, 1.0);
}