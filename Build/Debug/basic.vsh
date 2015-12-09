#version 330

layout(location = 0)in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 tangent;
layout(location = 4) in vec3 biTangent;

out vec3 position0;
out vec2 texCoord0;

void main(void){
    gl_Position = vec4(position, 1.0);

    position0 = position;
    texCoord0 = texCoord;
}