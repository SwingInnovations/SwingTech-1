
#version 400 core

in vec2 TexCoord;

uniform sampler2D tex;

out vec4 color;

float getLuma(vec3 color){

		vec3 luma = vec3(.02126,0.7152,0.0722);
		return dot(color,luma);
}
void main(void){
	vec3 c =texture2D(tex,TexCoord).rgb;
	if(getLuma(c)>1)
		color = texture2D(tex,TexCoord);
	else
	    color = vec4(0,0,0,1);
	  
	}