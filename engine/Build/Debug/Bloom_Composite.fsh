
#version 420 core

in vec2 TexCoord;

layout(binding=0) uniform sampler2D tex;

layout(binding=1) uniform sampler2D threshTex;

out vec4 color;

void main(void){
	float k =5;
	float radius=.03;
	vec3 sum=vec3(0);
	float brightness=pow(min(length(texture2D(threshTex, TexCoord)),1),2)*.5;
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){

			vec3 s =texture2D(threshTex, TexCoord + vec2(radius*(i/k),radius*(j/k)),4).rgb;
			
			sum += s;


		}
	}
 	radius=.007;
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){

			vec3 s =texture2D(threshTex, TexCoord + vec2(radius*(i/k),radius*(j/k)),6).rgb;
			
			sum += s;


		}
	}


	sum *=brightness;
	color= vec4(sum/pow(2*k+1,2)*2+texture2D(tex, TexCoord).rgb ,1);

	}