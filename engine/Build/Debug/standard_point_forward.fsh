#version 400 core

in vec3 Position;
in vec3 Normal;


uniform vec3 _LightPosition;
uniform float _LightAttenuation;
uniform float _LightRadius;
uniform vec3 _LightColor;
uniform vec3 _GlobalAmbient;



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




	vec3 dialectric = Diff+	Spec*.6;
	vec3 metal = Spec;

	return mix(dialectric,metal,_Metallic);
}




void main(void){
	vec3 V = normalize(_CameraPos - Position);
	vec3 L = normalize(_LightPosition - Position);
	vec3 H = normalize(V-L);

		
	

	float dist = length (L);
	float r = max(_Roughness,.1);

}