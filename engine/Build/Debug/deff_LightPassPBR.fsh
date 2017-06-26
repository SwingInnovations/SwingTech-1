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

uniform vec3 viewPos;

void main(void){
    vec3 FragPos = texture(gPosition, TexCoord).rgb;
    vec3 Normal = texture(gNormal, TexCoord).rgb;
    vec3 Tangent = texture(gTangent, TexCoord).rgb;
    vec3 Color = texture(gColorSpec, TexCoord).rgb;
    vec3 MRA = texture(gMRA, TexCoord).rgb;
    float specular = texture(gColorSpec, TexCoord).a;
    vec3 B = cross(Tangent, Normal);
    mat3 TBN = mat3(Tangent, B, Normal);


    vec3 lighting = Color * vec3(0.001);
    vec3 viewDir = normalize(_CameraPos - FragPos);

    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, Color, MRA.x);
    vec3 ambient = vec3(0.01) * Color * 1.0;
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < LightCount; i++){
        float bias = max(0.05 * (1.0 - dot(Normal, (Light[i].Position - FragPos))), 0.005);
        vec4 FPLS = transpose(Light[i].LightSpaceMatrix) * vec4(FragPos, 1.0);
        float shadow = calculateShadow(FPLS, shadowArray, 0, bias);

        if(Light[i].Direction.w == 0 || Light[i].Direction.w == 1){
            vec3 L = normalize(Light[i].Position - FragPos);
            vec3 H = normalize(V + L);
            float len = length(Light[i].Position - FragPos);
            float distance = (len == 0) ? len : 1;
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance = Light[i].Color * attenuation;

            float NDF = DistribGGX(N, H, MRA.y);
            float G = GeometrySmith(N, V, L, MRA.y);
            vec3 F = FresnelSchlick(max(dot(H,V), 0), F0);

            vec3 kS = F;
            vec3 kD = vec3(1.0) - kS;
            kD *= (1.0 - MRA.x);

            vec3 nom = NDF * G * F;
            float denom = 4 * max(dot(N,V), 0.0) * max(dot(N,L), 0.0) + 0.0001;
            vec3 specular = nom / (denom + 0.0001);

            float NdotL = max(dot(N,L), 0.0);
            Lo += (kD * Color / PI + specular) * radiance * NdotL;
        }
        lighting += ambient +  ((1.0 - shadow) * Lo);
        //lighting += DirectPBR((1.0 - shadow) * Color, MRA, FragPos, Normal, Light[i].Position, Light[i].Color, _CameraPos);
    }

    lighting = lighting / (lighting + vec3(1.0));
    lighting = pow(lighting, vec3(1.0 / 2.2));

    color = vec4(lighting, 1.0);

    //color = vec4(FragPos, 1.0);
}