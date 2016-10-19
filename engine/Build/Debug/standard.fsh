#version 400 core

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

struct STMaterial{
    sampler2D Diffuse_Tex;
    sampler2D Normal_Tex;
};

uniform STMaterial Material;

out vec4 color;

void main(void){
    color = texture(Material.Diffuse_Tex, TexCoord);
}