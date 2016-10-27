
#version 400 core

in vec2 TexCoord;

uniform sampler2D tex;

out vec4 color;

void main(void){
	vec3 c =texture2D(tex,TexCoord).rgb;
	if(length(sqrt(c.r*c.r+c.g*c.g+c.b*c.b))>1.5)
		color = texture2D(tex,TexCoord);
	else
	    color = vec4(0,0,0,1);
	  
	}