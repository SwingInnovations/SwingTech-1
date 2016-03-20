layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 texCoord0;

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

void main(void){
    gl_Position = projection * vec4(position, 1.0);
    texCoord0 = texCoord;
}