#version 330 core

in vec3 Position;
in vec3 Normal;


uniform vec3 _LightPosition;
uniform float _LightAttenuation;
uniform float _LightRadius;
uniform vec3 _LightColor;
uniform vec3 _GlobalAmbient;
uniform vec3 _CameraPos;

out vec4 color;

float PI = 3.14159265359;
float E =2.7182818284590452353602874713527;

float GGX_Clamp(float x){

	return x > 0 ? 1 : 0;
}

float Beckman_Dist(vec3 normal, vec3 H, float m){

	float expo = (pow(dot(normal,H),2)-1)/m*m*pow(dot(normal,H),2);
	return pow(E,expo)/PI*m*m*pow(dot(normal,H),4);
}


float Fresnel_Term( vec3 H, vec3 L, float n){

	float f0 = pow(abs((1-n)/(1+n)),2);

	return f0 + (1-f0) * pow( 1-dot(L,H),5 );
}


float Cook_Torrance_Geometry_Term( vec3 normal, vec3 H, vec3 V, vec3 L){

	float C1 = 2*dot(normal,H)*dot(normal,V)/dot(V,H);
	float C2 = 2*dot(normal,H)*dot(normal,L)/dot(V,H);

	return min(1,min(C1,C2));
}

/*float GGX_Geometry(vec3 Normal, vec3 H, vec3 view,float alpha){
	float alpha = roughness*roughness;
	float VdotH2= clamp(dot(view,H),0.0,1.0);
	float chi = GGX_Clamp(VdotH2/clamp(dot(view,Normal),0.0,1.0));
	VdotH2= VdotH2*VdotH2;
	float tan2 = (1-VdotH2)/VdotH2;
	return (chi*2)/(1+sqrt(1+alpha*alpha*tan2));
}

*/
void main(void){

	//vec3 diff =  _LightColor* max(dot(Normal, normalize(_LightPosition-Position)),0);
	//float atten = _LightRadius/(1/_LightAttenuation * length(_LightPosition-Position));
   //color = vec4(diff,1)*atten;//(_GlobalAmbient + vec4(diff,1))*atten;\

	vec3 L = normalize(_LightPosition-Position);
	vec3 V = normalize(Position-_CameraPos);
	vec3 H = normalize(L + V);
	float ior=1.8;
	float roughness =.072;
   //float ndotv = pow(1-dot(normalize(Position-_CameraPos),Normal),5);
	float Cook_Torrance =Fresnel_Term(H,L,ior);//*Cook_Torrance_Geometry_Term(Normal,H,V,L)*Beckman_Dist(Normal,H,roughness);
	//Cook_Torrance/=4*dot(Normal,L)*dot(Normal,V);
   color = vec4 (Cook_Torrance,Cook_Torrance,Cook_Torrance,1);
}



