#version 420 core

in vec2 TexCoord;

uniform float uPixelSize;
uniform float uFarPlane;

layout(binding = 0) uniform sampler2D screenAlbedo;
layout(binding = 1) uniform sampler2D screenDepth;

out vec4 color;

const float GOLDEN_ANGLE = 2.39996;
const float MAX_BLUR_SIZE = 20.0;
const float RAD_SCALE = 0.5;

float getBlurSize(float depth, float focusPoint, float focusScale)
{
    float coc = clamp((1.0 / focusPoint - 1.0 / depth)*focusScale, -1.0, 0.0);
    return abs(coc) * MAX_BLUR_SIZE;
}

vec3 DepthOfField(vec2 texCoord, float focusPoint, float focusScale)
{
    float centerDepth = texture(screenDepth, texCoord).r * uFarPlane;
    float centerSize = getBlurSize(centerDepth, focusPoint, focusScale);
    vec3 col = texture(uTexture, texCoord).rgb;
    float tot = 1.0;

    float radius = RAD_SCALE;
    for(float ang = 0.0; radius < MAX_BLUR_SIZE; ang += GOLDEN_ANGLE)
    {
        vec2 tc = texCoord + vec2(cos(ang), sin(ang)) * uPixelSize * radius;

        vec3 sampleColor = texture(screenAlbedo, tc).rgb;
        float sampleDepth = texture(screenDepth, tc).r * uFarPlane;
        float sampleSize = getBlurSize(sampleDepth, focusPoint, focusScale);
        if(sampleDepth > centerDepth)
        {
            sampleSize = clamp(sampleSize, 0.0, centerSize * 2.0);
        }
        float m = smoothstep(radius-0.5, radius+0.5, sampleSize);
        col += mix(color/tot, sampleColor, m);
        tot += 1.0;
        radius += RAD_SCALE/radius;
    }

    return col /= tot;
}

void main(void)
{
    vec3 dofContrib = DepthOfField(TexCoord, 1.0, 1.0);
    color = vec4(dofContrib, 1.0);
}