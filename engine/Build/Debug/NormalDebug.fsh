#version 400 core

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
in mat3 TBN;

struct STMaterial
{
	vec3 BaseColor;
	sampler2D Diffuse_Tex;
	sampler2D Normal_Tex;
};

uniform STMaterial Material;

out vec4 color;

void main(void){
   
	vec3 norm = TBN * texture( Material.Normal_Tex, TexCoord ).xyz* 2.0 - 1.0;

   color = vec4(dot(norm, vec3(1,1,1)));//vec4( norm, 1 );
}