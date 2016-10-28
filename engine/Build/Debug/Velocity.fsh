	
#version 400 core

in vec4 Position;
in vec4 LastPosition;


in vec2 TexCoord;

uniform sampler2D tex;

out vec4 color;

void main(void){
	
	vec2 b = (LastPosition.xy /LastPosition.w)*.5+.5;
	vec2 a = (Position.xy /Position.w)*.5+.5;
	    color = vec4(a-b ,0,1);
	  
	}