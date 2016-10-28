#version 420 core

in vec2 TexCoord;

layout(binding=0) uniform sampler2D tex;

layout(binding=1) uniform sampler2D Velocity;

float vScale;

out vec4 color;

void main(void){
	vec2 texelSize = 1.0 / vec2(textureSize(tex, 0));
	 vec2 screenCoords = TexCoord.xy * texelSize;
	 vec2 vel = texture2D(Velocity,TexCoord).rg;
	 vel*= .3;
	 float speed = length(vel/texelSize);
	 color = texture2D(tex, TexCoord);

	for(int i=1; i< 50; i++ ){
		vec2 offset = vel * ((float(i) / 49.0)-0.5);
		color += texture2D(tex, TexCoord+offset );

	}

    color /=50.0;

}