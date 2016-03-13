layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 TexCoord;

uniform mat4 camera;
uniform mat4 model;

void main(void){
    gl_Position = model * vec4(position, 1.0);

    TexCoord = texCoord;
}