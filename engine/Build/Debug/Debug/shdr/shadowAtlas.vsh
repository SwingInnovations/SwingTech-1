#version 400 core

layout(location = 0) in vec4 points;
uniform mat4 projection;

out vec2 TexCoord;

void main(void){
    gl_PointSize = 5;
    gl_Position = transpose(projection) * vec4(points.xy, 0.0, 1.0);
    TexCoord = points.zw;
}