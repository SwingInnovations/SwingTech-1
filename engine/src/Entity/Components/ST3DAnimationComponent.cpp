#include "ST3DAnimationComponent.h"


void ST3DAnimationComponent::init(STEntity* parent) {
    m_entity = parent;
    m_gfxComponent = m_entity->get<STGraphicsComponent>();
}

ST3DAnimationComponent::ST3DAnimationComponent() {

}

ST3DAnimationComponent::ST3DAnimationComponent(const ST3DAnimationComponent &copy) {

}

void ST3DAnimationComponent::update() {

}

ST3DAnimationComponent::ST3DAnimationComponent(STMesh_Structure &meshStructure) {
    for(auto anim : meshStructure.m_animations){
        m_animationMap[anim->name] = anim;
    }
    m_boneData = meshStructure.m_boneData;
    m_nodeData = meshStructure.m_node;
}

void ST3DAnimationComponent::setCurrentAnimation(const std::string& animation) {
    m_currentAnimation = animation;
}

stUint ST3DAnimationComponent::FindPosition(stReal animationTime, STNodeAnim *node) {
    for(stUint i = 0; i < node->m_positions.size() - 1; i++){
        if(animationTime < node->m_positions[i+1]->m_time) return i;
    }
    return 0;
}

stUint ST3DAnimationComponent::FindRotation(stReal animationTime, STNodeAnim *node) {
    for(stUint i = 0; i < node->m_rotations.size() - 1; i++){
        if(animationTime < node->m_rotations[i+1]->m_time) return i;
    }
    return 0;
}

stUint ST3DAnimationComponent::FindScale(stReal animation, STNodeAnim *node) {
    for(stUint i = 0; i < node->m_scalings.size() - 1; i++){
        if(animation < node->m_scalings[i+1]->m_time) return i;
        }
    return 0;
}

void ST3DAnimationComponent::CalcInterpolatedPosition(Vector3D &out, float animTime, STNodeAnim *node) {
    if(node->m_positions.size() == 1){
        out = node->m_positions[0]->m_Value;
        return;
    }

    stUint PositionIndex = FindPosition(animTime, node);
    stUint NextPositionIndex = PositionIndex + 1;
    assert(NextPositionIndex < node->m_positions.size());
    stReal dt = node->m_positions[NextPositionIndex]->m_time - node->m_positions[PositionIndex]->m_time;
    stReal factor = (animTime - node->m_positions[PositionIndex]->m_time) / dt;
    assert(factor >= 0.0f && factor <= 1.0f);
    const Vector3D start = node->m_positions[PositionIndex]->m_Value;
    const Vector3D end = node->m_positions[NextPositionIndex]->m_Value;
    auto dV = end - start;
    out = start + (dV * factor);
}

void ST3DAnimationComponent::CalcInterpolatedRotation(Quaternion &out, float animTime, STNodeAnim *node) {

}

void ST3DAnimationComponent::CalcInterpolatedScaling(Vector3D &out, float animTime, STNodeAnim *node) {
    if(node->m_scalings.size() == 1){
        out = node->m_scalings[0]->m_Value;
    }

    stUint PositionIndex = FindScale(animTime, node);
    stUint NextPositionIndex = PositionIndex + 1;
    assert(NextPositionIndex < node->m_scalings.size());
    stReal dt = node->m_scalings[NextPositionIndex]->m_time - node->m_scalings[PositionIndex]->m_time;
    stReal factor = (animTime - node->m_scalings[PositionIndex]->m_time) / dt;
    assert(factor >= 0.f && factor <= 1.f);
    const Vector3D start = node->m_scalings[PositionIndex]->m_Value;
    const Vector3D end = node->m_scalings[NextPositionIndex]->m_Value;
    auto dV = end - start;
    out = start + (dV * factor);
}
