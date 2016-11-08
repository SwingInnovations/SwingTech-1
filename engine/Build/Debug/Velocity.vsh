#version 400 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texCoord;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 tangent;
layout(location = 4)in vec3 biTangent;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 cachedMVP;
out vec4 Position;
out vec4 LastPosition;
out vec2 TexCoord;


void main(void){
    gl_Position = projection * view * model * vec4(position, 1.0);

    Position =( projection * view * model * vec4(position, 1.0));
    LastPosition = (cachedMVP * vec4(position, 1.0));
    TexCoord = texCoord;


 
}