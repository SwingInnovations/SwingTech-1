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
uniform vec3 lightColor;
uniform samplerCube skyBox;

out vec4 color;

void main(void){

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - position0);

    float specStrength = 0.5;
    vec3 viewDir = normalize(cameraPosition - position0);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 reflectCol = reflect(viewDir, norm);

    vec4 reflectionTex = vec4(texture(skyBox, reflectCol) * 0.2);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specStrength * spec * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 objColor = vec3(1.0, 0.5, 0.31);
    vec3 diffColor = ((texture2D(diffuse, texCoord0).xyz * diff) * 0.5) + (reflectionTex.xyz);
    //vec3 diffColor = ((objColor * diff) * 0.5) + (reflectionTex.xyz * diff);
    vec3 result = (diffColor + specular);
    color = vec4(result, 1.0);
}
