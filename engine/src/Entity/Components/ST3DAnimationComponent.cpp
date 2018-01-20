#include "ST3DAnimationComponent.h"


void ST3DAnimationComponent::init(std::shared_ptr<STEntity>& entity) {
    m_entity = entity;
    m_gfxComponent = m_entity->get<STGraphicsComponent>();
}

ST3DAnimationComponent::ST3DAnimationComponent() {

}

ST3DAnimationComponent::ST3DAnimationComponent(const ST3DAnimationComponent &copy) {

}

void ST3DAnimationComponent::update() {
    auto time = SDL_GetTicks()/1000.f;
    MoveBones(time);
}

ST3DAnimationComponent::ST3DAnimationComponent(STMesh_Structure &meshStructure) {
    for(auto anim : meshStructure.m_Animations){
        m_animationMap[anim->name] = anim;
    }
    m_currentAnimation = meshStructure.m_Animations[0]->name;
    m_boneData = meshStructure.m_BoneData;
    m_nodeData = meshStructure.m_Node;
    m_boneMap  = meshStructure.m_boneMap;
    m_globalInverseMat = meshStructure.globalInverseMat;
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
    if(node->m_rotations.size() == 1){
        out = node->m_rotations[0]->m_value;
        return;
    }

    stUint RotationIndex = FindRotation(animTime, node);
    stUint NextRotationIndex = RotationIndex+1;
    assert(NextRotationIndex < node->m_rotations.size());
    stReal dt = node->m_rotations[NextRotationIndex]->m_time - node->m_rotations[RotationIndex]->m_time;
    stReal factor = (animTime - node->m_rotations[RotationIndex]->m_time) / dt;
    assert(factor >= 0.f && factor <= 1.f);
    auto start = node->m_rotations[RotationIndex]->m_value;
    auto end = node->m_rotations[NextRotationIndex]->m_value;
    out = Quaternion::slerp(start, end, factor).normalize();
}

void ST3DAnimationComponent::CalcInterpolatedScaling(Vector3D &out, float animTime, STNodeAnim *node) {
    if(node->m_scalings.size() == 1){
        out = node->m_scalings[0]->m_Value;
        return;
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



void ST3DAnimationComponent::ReadNodeHeirarchy(float AnimationTime, STMeshNode *node, Matrix4f &parentTransform) {
    auto anim = m_animationMap[m_currentAnimation];
    Matrix4f nodeTransform = node->transform;
    auto animNode = FindAnimMode(anim.get(), node->m_Name);
    if(animNode){
        Vector3D scaling;
        CalcInterpolatedScaling(scaling, AnimationTime, animNode);
        Matrix4f scaleM;
        scaleM.initScale(scaling);

        Quaternion rot;
        CalcInterpolatedRotation(rot, AnimationTime, animNode);
        Matrix4f rotM;
        rotM.initRotation(rot);

        Vector3D translation;
        CalcInterpolatedPosition(translation, AnimationTime, animNode);
        Matrix4f transM;
        transM.initTranslation(translation);

        //nodeTransform = scaleM * rotM * transM;
        nodeTransform = transM * rotM * scaleM;
    }

    Matrix4f GlobalTransform = parentTransform * nodeTransform;

    if(m_boneMap.find(node->m_Name) != m_boneMap.end()){
        stUint boneIndex = m_boneMap[node->m_Name];
        m_boneData[boneIndex]->m_finalTransformation = GlobalTransform * m_boneData[boneIndex]->m_offsetMatrix;
    }

    for(auto child : node->m_Children){
        ReadNodeHeirarchy(AnimationTime, child.get(), GlobalTransform);
    }
}

STNodeAnim *ST3DAnimationComponent::FindAnimMode(STAnimation *animation, std::string nodeName) {
    for (auto nodeAnim : animation->m_channels) {
        if(nodeAnim->name == nodeName){
            return nodeAnim;
        }
    }
    return nullptr;
}

void ST3DAnimationComponent::MoveBones( stReal animationTime) {
    Matrix4f Ident;
    auto anim = m_animationMap[m_currentAnimation];
    if(anim){
        stReal TicksPerSecond = m_animationMap[m_currentAnimation]->m_TicksPerSecond != 0 ? m_animationMap[m_currentAnimation]->m_TicksPerSecond : 25.f;
        stReal TimeInTicks = animationTime * TicksPerSecond;
        float AnimationTime = fmodf(TimeInTicks, m_animationMap[m_currentAnimation]->m_Duration);
        ReadNodeHeirarchy(AnimationTime, m_nodeData.get(), Ident);

        if(m_gfxComponent == nullptr) m_gfxComponent = getParent()->get<STGraphicsComponent>();
        if(m_gfxComponent!= nullptr){
            for(stUint i = 0; i < m_boneData.size(); i++){
                m_gfxComponent->setShdrUniform("gBones["+std::to_string(i)+"]", m_boneData[i]->m_finalTransformation);
            }
        }
    }else{
        if(m_gfxComponent != nullptr){
            for(stUint i = 0; i < m_boneData.size(); i++){
                m_gfxComponent->setShdrUniform("gBones["+std::to_string(i)+"]", Ident);
            }
        }
    }
}

ST3DAnimationComponent::~ST3DAnimationComponent() {
    m_boneData.clear();
    m_nodeData.reset();
    m_boneMap.clear();
    m_animationMap.clear();
}

void ST3DAnimationComponent::initScriptingFunctions(sol::state& script) {
    script.set_function("get3DAnimationComponent", [](STEntity* ent){
        return ent->get<ST3DAnimationComponent>();
    });
    script.new_usertype<ST3DAnimationComponent>("ST3DAnimation",
                                                "setCurrentAnimation", &ST3DAnimationComponent::setCurrentAnimation);
}

void ST3DAnimationComponent::save(std::ofstream &out) {

}

void ST3DAnimationComponent::load(std::ifstream &in) {

}

REGISTER_COMPONENT(ST3DAnimationComponent)