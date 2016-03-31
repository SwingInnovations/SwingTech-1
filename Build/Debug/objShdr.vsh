#version 330 core

layout(location = 0)in vec3 position;
layout(location = 2)in vec3 texCoord;

uniform mat4 camera;
uniform mat4 projection;

void main(void){
    gl_Position = vec4(position.x, position.y, 0, 1.0);
}