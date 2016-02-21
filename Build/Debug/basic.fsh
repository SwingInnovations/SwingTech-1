#version 330 core

in vec3 position0;
in vec2 texCoord0;
in vec3 lightDir0;
in vec3 Normal;

uniform float uniR;
uniform float uniG;
uniform float uniB;
uniform vec3 lightPos;
uniform vec3 cameraPosition;
uniform sampler2D diffuse;
uniform vec3 objColor;

out vec4 color;

void main(void){

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - position0);

    float specStrength = 0.5f;
    vec3 viewDir = normalize(cameraPosition - position0);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specStrength * spec * vec3(1.0);

    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 objColor = vec3(1.0, 0.5, 0.31) * diff;
    vec3 diffColor = objColor * diff;
    vec3 result = (diffColor + specular);
    //color = vec4(result, 1.0);
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
