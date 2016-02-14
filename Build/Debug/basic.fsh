#version 330 core

in vec3 position0;
in vec2 texCoord0;
in vec3 lightDir0;

uniform float uniR;
uniform float uniG;
uniform float uniB;
uniform vec3 lightPos;
uniform sampler2D diffuse;

out vec4 color;


void main(void){
    float shading = max(0.0, dot(position0, lightDir0));
    vec3 diffuse = texture2D(diffuse, texCoord0).rgb;
    //color = vec4(clamp(uniR, 0.0, 1.0), clamp(uniG, 0.0, 1.0), clamp(uniB, 0.0, 1.0), 1.0) * shading;
    color = vec4(diffuse, 1.0) * shading;
}
