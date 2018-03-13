#version 420 core

#define EDGE_THRESHOLD_MIN (1.0/32.0)
#define EDGE_THRESHOLD (1.0/8.0)

in vec2 TexCoord;

layout(binding=0) uniform sampler2D tex;



out vec4 color;



float getLuma(vec3 color){

		vec3 luma = vec3(.02126,0.7152,0.0722);
		return dot(color,luma);
}

float scale =7;
void main(void){

	vec2 size = vec2(textureSize(tex,0));

	vec3 CN = texelFetch(tex, ivec2(size*TexCoord) + ivec2(0,1), 0).rgb;
	vec3 CS = texelFetch(tex, ivec2(size*TexCoord) + ivec2(0,-1), 0).rgb;
	vec3 CE = texelFetch(tex, ivec2(size*TexCoord) + ivec2(1,0), 0).rgb;
	vec3 CW = texelFetch(tex, ivec2(size*TexCoord) + ivec2(-1,0), 0).rgb;
	vec3 CM = texelFetch(tex, ivec2(size*TexCoord) , 0).rgb;
	float LN = getLuma(CN);
	float LS = getLuma(CS);
	float LE = getLuma(CE);
	float LW = getLuma(CW);
	float LM = getLuma(CM);
	float L_min = min(LM,min(min(LN,LW),min(LS,LE)));
	float L_max = max(LM,max(max(LN,LW),max(LS,LE)));
	float contrast = L_max-L_min;

	if(contrast >= max(EDGE_THRESHOLD_MIN, L_max * EDGE_THRESHOLD))
	{
		vec3 CNW = texelFetch(tex, ivec2(size*TexCoord) + ivec2(-1,1), 0).rgb;
		vec3 CNE = texelFetch(tex, ivec2(size*TexCoord) + ivec2(1,1), 0).rgb;
		vec3 CSW = texelFetch(tex, ivec2(size*TexCoord) + ivec2(1,-1), 0).rgb;
		vec3 CSE = texelFetch(tex, ivec2(size*TexCoord) + ivec2(-1,-1), 0).rgb;
		
		color =vec4((CN+CS+CE+CW+CM+CNW+CNE+CSW+CSE) / 9.0,1);

		float NW = getLuma((CN+CW+CNW+CM)/4.0);
		float NE = getLuma((CN+CE+CNE+CM)/4.0);
		float SW = getLuma((CS+CW+CSW+CM)/4.0);
		float SE = getLuma((CS+CE+CSE+CM)/4.0);	
		vec2 dir = vec2(-((NW+NE)-(SW+SE)),((NW+SW)-(NE+SE)));
		dir*=scale/size;
		;

		for(int i=1; i< 10; ++i ){
				vec2 offset = 2*dir * (float(i) / float(10-1) -0.5);
		
				color += texture2D(tex, TexCoord+offset);
	
		}
			color/=10;
		
		
		return;
	}

		color = texture(tex, TexCoord);
		//color = vec4(0,0,0,1);
}






