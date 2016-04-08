#version 330 core

layout(location = 0) in vec3 position;

out vec3 Texcoord;

uniform mat4 view;
uniform mat4 projection;

void main(void){
    vec4 pos = projection * view * vec4(position, 1.0) * 1000;
    gl_Position = pos.xyww;
    Texcoord = position;
}