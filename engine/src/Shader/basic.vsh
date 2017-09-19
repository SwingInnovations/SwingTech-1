in vec3 position;
in vec2 texCoord;

uniform mat4 model;

out vec3 position0;
out vec2 texCoord0;

void main(void){
    gl_Position = vec4(position, 1.0);

    position0 = position;
    texCoord0 = texCoord;
}