#INSERT_HEADER

#include <STLight.glinc>
#include <shadow_vert.glinc>

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texCoord;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 tangent;
layout(location = 4)in vec3 biTangent;
layout(location = 5)in ivec4 boneID;
layout(location = 6)in vec4 boneWeights;

#define MAX_BONES 100

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;
uniform STLight lights[10];
uniform mat4 gBones[100];

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;
out mat3 TBN;
out vec3 Tangent;
out vec4 FragPosLightSpace;
out ShadowSpecs shadowSpecs[64];

void main(void){
    mat4 BoneTransform = gBones[boneID.x] * boneWeights.x;
    BoneTransform +=     gBones[boneID.y] * boneWeights.y;
    BoneTransform +=     gBones[boneID.z] * boneWeights.z;
    BoneTransform +=     gBones[boneID.w] * boneWeights.w;

    vec4 posL = transpose(BoneTransform) * vec4(position, 1.0);

    gl_Position = projection * view * model * posL;

    Position = (model * posL).xyz;

    TexCoord = texCoord;

    vec3 T = vec3(model * vec4(tangent,   0.0));
    Tangent = T;

    vec4 NormalL = transpose(BoneTransform) * vec4(normal, 0.0);

  	//vec3 N = vec3(model * vec4(normal,    0.0));
  	vec3 N = vec3(model * NormalL);

	vec3 B = cross(T, N);

	Normal = N;

    TBN = mat3(T, B, N);

    FragPosLightSpace = transpose(lightSpaceMatrix) * transpose(BoneTransform) * vec4(Position, 1.0);
}