#version 400 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in mat3 TBN;

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


vec3 BlendMaterial(vec3 Spec, vec3 Diff, vec3 Base){

	
	
	vec3 dialectric =Base*Diff+	Base*Spec*.6;
	vec3 metal = Base*Spec;

	return mix(dialectric,metal,_Metallic)*Light.Intensity;
}




void main(void){

	vec3 Norm =  (TBN* (texture2D(Material.Normal_Tex,TexCoord).xyz*2-1));

	float r = max(_Roughness,.1);
	vec3 V=normalize(_CameraPos-Position);
	vec3 H = normalize(V-Light.Direction*1000);

	vec3 spec = clamp(vec3(Ggx_Dist_old(dot(Norm, H),r)),0,1);
	vec3 diff = clamp(vec3(Ggx_Dist_old(dot(Norm, H),1)),0,1);
	
	color =  vec4(BlendMaterial(spec,diff,Material.BaseColor ),1);
}