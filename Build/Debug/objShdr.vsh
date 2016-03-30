#version 330 core

layout(location = 0)in vec3 position;
layout(location = 2)in vec3 texCoord;

uniform mat4 model;
uniform mat4 view;

void main(void){
    gl_Position = view * vec4(position, 1.0);
}