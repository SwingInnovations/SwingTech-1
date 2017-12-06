#version 330 core

in vec2 TexCoord;

uniform sampler2D tex;

out vec4 color;

void main(void){
    vec4 tex = texture(tex, TexCoord);
    if(gl_FragCoord.x > 720){
        color = vec4(tex.x, tex.x, tex.x, 1.0);
    }else{
        color = tex;
    }
}