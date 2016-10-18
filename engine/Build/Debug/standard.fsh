#version 330 core

in vec3 Position;
in vec3 Normal;

uniform vec3 objColor;
uniform vec3 _Direction;

out vec4 color;

void main(void){

	float diff =min(1,max(0,dot(Normal, _Direction)));
   color =  vec4(objColor,1)+vec4(diff,diff,diff,1);
}