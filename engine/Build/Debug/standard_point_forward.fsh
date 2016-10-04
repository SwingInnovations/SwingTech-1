#version 330 core

in vec3 Position;
in vec3 Normal;


uniform vec3 _LightPosition;
uniform float _LightAttenuation;
uniform float _LightRadius;
uniform vec3 _LightColor;
uniform vec3 _GlobalAmbient;

out vec4 color;

void main(void){

	vec3 diff =  _LightColor* max(dot(Normal, normalize(_LightPosition-Position)),0);
	float atten = _LightRadius/(1/_LightAttenuation * length(_LightPosition-Position));
   color = vec4(diff,1)*atten;//(_GlobalAmbient + vec4(diff,1))*atten;
}