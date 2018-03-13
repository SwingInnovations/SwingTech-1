#version 420 core

in vec2 TexCoord;

layout(binding=0) uniform sampler2D tex;

out vec4 color;

void main(void){

	vec3 resColor = texture2D(tex ,TexCoord).rgb;
	resColor *= .5;
	resColor = resColor/ (1+resColor);
	color = vec4(pow(resColor.r,1.0/2.2),pow(resColor.g,1.0/2.2),pow(resColor.b,1.0/2.2),1);
}