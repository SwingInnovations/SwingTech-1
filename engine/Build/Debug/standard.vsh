#version 330 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texCoord;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 tangent;
layout(location = 4)in vec3 biTangent;

uniform mat4 model;
uniform mat4 camera;


out vec3 Position;
out vec3 Normal;

void main(void){
    gl_Position = camera * model * vec4(position, 1.0);

    Position = (model * vec4(position, 1.0)).xyz;
    Normal = ( vec4(normal, 1.0)).xyz;

}