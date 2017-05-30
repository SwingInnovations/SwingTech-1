#INCLUDE_HEADER

#include<standard.glinc>
#include<shadow.glinc>

//TODO Implement standard shading
void main(void){
    vec3 lighting = ColorEval3x4(texture(Material.Diffuse_Tex, TexCoord).rgb, Material.Diffuse_Color) * 0.1;
    vec3 col = ColorEval3x4(texture(Material.Diffuse_Tex, TexCoord));
    for(int i = 0; i < LightCount; i++){
        vec3 lightDir = (Light[i].Position - Position);

        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * col * Light[i].Color;
        lighting += diffuse;
    }
    color = vec4(lighting, 1.0);
}