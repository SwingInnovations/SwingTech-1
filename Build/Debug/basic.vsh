#version 330 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texCoord;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 tangent;
layout(location = 4)in vec3 biTangent;

uniform mat4 model;
uniform mat4 camera;
uniform vec3 camPos;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 position0;
out vec2 texCoord0;
out vec3 lightDir0;

void main(void){
    gl_Position = projection * view * model * vec4(position, 1.0);

    position0 = (model * vec4(position, 1.0)).xyz;
    Normal = (model * vec4(normal, 1.0)).xyz;
    texCoord0 = texCoord;
    lightDir0 = vec3(0.5, 1.0, -1.0);
}