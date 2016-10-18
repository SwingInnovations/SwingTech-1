#version 330 core

in vec3 Position;
in vec3 Normal;

uniform vec3 objColor;
uniform vec3 _GlobalAmbient;


out vec4 color;

void main(void){
   color =  vec4(_GlobalAmbient,1);

}