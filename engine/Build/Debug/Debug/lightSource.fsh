#version 330 core

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

uniform vec3 objColor;
uniform sampler2D tex;

out vec4 color;

void main(void){
   //color = vec4(objColor, 1.0);
   color = texture(tex, TexCoord);
}