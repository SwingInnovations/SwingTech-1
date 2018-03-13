#version 400 core

layout(location = 0) in vec3 position;
layout(location = 5) in ivec4 boneID;
layout(location = 6) in vec4 boneWeights;

uniform mat4 shadow_model;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform mat4 gBones[100];

void main(void){
    mat4 BoneTransform = gBones[boneID.x] * boneWeights.x;
    BoneTransform +=     gBones[boneID.y] * boneWeights.y;
    BoneTransform +=     gBones[boneID.z] * boneWeights.z;
    BoneTransform +=     gBones[boneID.w] * boneWeights.w;

    gl_Position = transpose(lightSpaceMatrix) * model * transpose(BoneTransform) * vec4(position, 1.0f);
}