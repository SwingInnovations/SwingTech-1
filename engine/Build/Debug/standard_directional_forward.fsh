#version 400 core

in vec3 Position;
in vec3 Normal;


uniform vec3 _LightDirection;
uniform vec3 _LightColor;
uniform vec3 _GlobalAmbient;
uniform float _LightAttenuation;
out vec4 color;

void main(void){

	vec3 diff = _LightColor* max(dot(Normal, _LightDirection),0);
   color =  vec4(diff,1)* _LightAttenuation;;
}