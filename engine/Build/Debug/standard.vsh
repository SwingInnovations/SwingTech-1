#version 400 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texCoord;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 tangent;
layout(location = 4)in vec3 biTangent;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 view;

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;
out mat3 TBN;

void main(void){
    gl_Position = camera * model * vec4(position, 1.0);

    Position = (model * vec4(position, 1.0)).xyz;

    TexCoord = texCoord;
     vec3 T = (vec3(transpose(inverse((model))) * vec4(tangent,   0.0)));
   vec3 B = (vec3(transpose(inverse((model))) * vec4(biTangent, 0.0)));
   vec3 N = (vec3(transpose(inverse((model))) * vec4(normal,    0.0)));
    TBN = mat3(tangent, biTangent, normal);
    Normal = transpose(inverse(mat3(model))) * normal;

}