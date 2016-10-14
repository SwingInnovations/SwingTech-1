#version 400 core

in vec3 Position;
in vec3 Normal;


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

	vec3 dialectric = Base*Diff + Base*	Spec*.6;
	vec3 metal = Base*Spec;

	return mix(dialectric,metal,_Metallic);
}




void main(void){
	vec3 V = normalize(_CameraPos - Position);
	vec3 L = normalize(Light.Position - Position);
	vec3 H = normalize(V-L);

		
	

	float dist = length (Light.Position - Position) ;
	float r = max(_Roughness,.1);
	float I = dot(-Normal,H) * (Light.Radius/(Light.Intensity+Light.Intensity*dist+Light.Intensity*dist*dist)) ;
	vec3 spec =vec3(Ggx_Dist_old(dot(-Normal,H),r));
	vec3 diff = vec3(Ggx_Dist_old(I,1));
	color = vec4(BlendMaterial(spec,diff,Light.Color),1);

}