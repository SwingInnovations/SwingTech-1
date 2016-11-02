#version 420 core

in vec2 TexCoord;

layout(binding=0) uniform sampler2D tex;

layout(binding=1) uniform sampler2D Velocity;



out vec4 color;

void main(void){
	float vScale=.8;

	vec2 texelSize = 1.0 / vec2(textureSize(tex, 0));

	

	vec2 vel = texture2D(Velocity,TexCoord).rg;
	vel *=vScale;

 	float speed = length( vel / texelSize);
  	int Samples = clamp(int(speed), 1, 70);

	color = texture2D(tex, TexCoord);
	float w=0;
	for(int i=1; i< Samples; ++i ){
		vec2 offset = vel * (float(i) / float(Samples-1) -0.5);

		color += texture2D(tex, TexCoord+offset);
	
	}

    color /=float(Samples);
    color.a=1;
}