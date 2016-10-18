#version 330 core

in vec3 Position;
in vec3 Normal;

varying vec3 vertPos;

uniform float _LightAttenuation;

uniform vec3 _LightColor;
uniform vec3 _GlobalAmbient;
uniform vec3 _CameraPos;
uniform vec3 _LightDirection;
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

float Ggx_Dist(vec3 normal, vec3 H, float r){
	float alpha = r*r;

	float alpha2= alpha*alpha;

	float denom = (dot(normal,H)*dot(normal,H) * (alpha2-1)) + 1;
	return alpha2/(PI*denom*denom);
}

float Ggx_Dist_old(vec3 normal, vec3 H, float r){
	float alpha = r*r;

	float alpha2= alpha*alpha;
	float ndoth = dot(normal,H);
	float ndoth2= ndoth*ndoth;
	float denom = ndoth2*alpha2+(1-ndoth2);
	return ((ndoth) *alpha2)/(PI*denom*denom);
}




float Fresnel_Term( vec3 H, vec3 V, float ior){

	float f0 = pow(abs((1-ior)/(1+ior)),2);

	return f0 + (1-f0) * pow(2, (-5.55473*dot(V,H)-6.98316)*dot(V,H));
}


float Cook_Torrance_Geometry_Term( vec3 normal, vec3 H, vec3 V, vec3 L){

	float C1 = 2*dot(normal,H)*dot(normal,V)/dot(V,H);
	float C2 = 2*dot(normal,H)*dot(normal,L)/dot(V,H);

	return min(1,min(C1,C2));
}


float Schlick_Geometry_Hack_Partial( vec3 normal, vec3 H, vec3 V, float r){

	float k = (r+1)*(r+1)/8;
	return  dot(normal,V) / (dot(normal,V)*(1-k)+k);
}

float Schlick_Geometry_Hack( vec3 normal, vec3 H, vec3 V, vec3 L, float r){

	
	return Schlick_Geometry_Hack_Partial(normal,H,L,r)*Schlick_Geometry_Hack_Partial(normal,H,V,r);
}

float Vis_Shlick( vec3 normal, vec3 H, vec3 V, vec3 L, float r){

	
	float k = r  * 0.5;
	float Vis_SchlickV = dot(normal,V) * (1 - k) + k;
	float Vis_SchlickL = dot(normal,L) * (1 - k) + k;
	return 0.25 / ( Vis_SchlickV * Vis_SchlickL );

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

	vec3 L = normalize( _LightDirection  );
	vec3 V = normalize( _CameraPos - Position  );
	vec3 H = normalize(L + V);
	float ior=1.2;
	float f0 = pow(abs((1-ior)/(1+ior)),2);
	float roughness = .048;
	vec3 diffColor= vec3(1,0,0);
   //float ndotv = pow(1-dot(normalize(Position-_CameraPos),Normal),5);
	float Cook_Torrance =Ggx_Dist(Normal,H,roughness)*Fresnel_Term(H,V,ior)*Schlick_Geometry_Hack(Normal, H,V,L,roughness) ;//
	Cook_Torrance/=4*dot(Normal,L)*dot(Normal,V);
    color = vec4 (Cook_Torrance,Cook_Torrance,Cook_Torrance,1);
}



