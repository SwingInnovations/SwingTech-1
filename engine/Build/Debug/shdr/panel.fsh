in vec2 TexCoord;

uniform vec3 backgroundColor;
uniform vec3 foregroundColor;

out vec4 Frag;

void main(void){
    Frag = vec4(foregroundColor, 1.0);
}