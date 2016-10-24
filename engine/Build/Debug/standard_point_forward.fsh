#version 400 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in mat3 TBN;

in vec4 FragPosLightSpace;

uniform vec3 _LightPosition;
uniform float _LightAttenuation;
uniform float _LightRadius;
uniform vec3 _LightColor;
uniform vec3 _GlobalAmbient;


struct STLight
{
	vec3 Color;
	vec3 Position;
	vec3 Direction;
	float Radius;
	float Intensity;

};

uniform STLight Light;

struct STMaterial
{
	vec3 BaseColor;
	sampler2D Diffuse_Tex;
	sampler2D Normal_Tex;
};
uniform sampler2D shadowMap;

uniform STMaterial Material;

uniform vec3 _CameraPos;

uniform float _Metallic;
uniform float _Roughness;

float PI = 3.14159265359;

out vec4 color;


float Ggx_Dist_old(float NdotH, float r){
	float alpha = r*r;

	float alpha2= alpha*alpha;
	
	float ndoth2=NdotH*NdotH;
	float denom = ndoth2*alpha2+(1-ndoth2);
	return ((NdotH) *alpha2)/(PI*denom*denom);
}

float CalculateShadow(vec4 fragPos){
    vec3 projCoord = fragPos.xyz / fragPos.w;
    projCoord = projCoord * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoord.xy).r;
    float currentDepth = projCoord.z;
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
    return shadow;
}

vec3 BlendMaterial(vec3 Spec, vec3 Diff, vec3 Base){
    float s = CalculateShadow(FragPosLightSpace);
	vec3 dialectric = (1.0 - s) * Light.Color * Base * Diff + Light.Color*Spec*.6;
	vec3 metal = (1.0 - s) * Base*Spec;

	return mix(dialectric,metal,_Metallic);
}

void main(void){


	vec3 Norm = (TBN* (texture2D(Material.Normal_Tex,TexCoord).xyz*2-1));

	vec3 V = normalize(_CameraPos - Position);
	vec3 L = normalize(Light.Position - Position);
	vec3 H = normalize(V-L);

    float shadow = CalculateShadow(FragPosLightSpace);
	

	float dist = length (Light.Position - Position) ;
	float r = max(_Roughness,.1);
	float I = dot(Norm,H) * (Light.Radius/(Light.Intensity+Light.Intensity*dist+Light.Intensity*dist*dist)) ;
	vec3 spec =vec3(Ggx_Dist_old(dot(Norm,H),r));
	vec3 diff = vec3(Ggx_Dist_old(I,1));
	vec3 baseColor = Material.BaseColor  ;
	color = vec4((1.0 - shadow) * BlendMaterial(spec,diff,baseColor),1);
}