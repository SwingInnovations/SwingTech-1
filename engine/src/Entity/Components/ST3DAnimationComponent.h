#ifndef SWINGTECH1_ST3DANIMATIONCOMPONENT_H
#define SWINGTECH1_ST3DANIMATIONCOMPONENT_H

#include "STComponent.h"
#include "STGraphicsComponent.h"
#include "../STEntity.h"

class STComponent;

/**
 * @brief Handle Animation of Character(supplied by file)
 */
class ST3DAnimationComponent : public STComponent {
public:
    explicit ST3DAnimationComponent();
    ST3DAnimationComponent(STMesh_Structure& meshStructure);
    ST3DAnimationComponent(const ST3DAnimationComponent& copy);
    void loadBones();
    void init(STEntity* parent);
    void update() override ;
    void setCurrentAnimation(const std::string& anim);
protected:
    bool                                m_isRoot;
    std::string                         m_currentAnimation;
    STGraphicsComponent*                m_gfxComponent;
    std::map<std::string, STAnimation*> m_animationMap;
    STList<STBoneData*>                 m_boneData;
    STMeshNode*                         m_nodeData;
private:
    stUint FindPosition(stReal animationTime, STNodeAnim* node);
    stUint FindRotation(stReal animationTime, STNodeAnim* node);
    stUint FindScale(stReal animation, STNodeAnim* node);

    void CalcInterpolatedPosition(Vector3D& out, float animTime, STNodeAnim* node);
    void CalcInterpolatedRotation(Quaternion& out, float animTime, STNodeAnim* node);
    void CalcInterpolatedScaling(Vector3D& out, float animTime, STNodeAnim* node);
};


#endif //SWINGTECH1_ST3DANIMATIONCOMPONENT_H
