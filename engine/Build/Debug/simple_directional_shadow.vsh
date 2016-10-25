#version 400 core

layout(location = 0) in vec3 position;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main(void){
    gl_Position = transpose(lightSpaceMatrix) * model * vec4(position, 1.0f);
}