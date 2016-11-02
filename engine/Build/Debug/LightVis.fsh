#version 400 core

in vec3 lightColor;

out vec4 FragColor;

void main(void){
    FragColor = vec4(lightColor, 1.0);
}
