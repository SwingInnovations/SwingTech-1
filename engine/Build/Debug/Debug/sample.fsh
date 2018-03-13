in vec2 texCoord0;

uniform sampler2D tex;

out vec4 color;

void main(void){
    color = texture(tex, texCoord0 );
}