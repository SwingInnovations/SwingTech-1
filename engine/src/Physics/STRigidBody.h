#ifndef SWINGTECH1_STRIGIDBODY_H
#define SWINGTECH1_STRIGIDBODY_H

#include "../Math/STCore.h"

class Transform;

/**
 * Template class for defining rigid body
 */
class STRigidBody{
public:
    enum RigidBodyShape : unsigned char{
        BOX,
        SPHERE,
        CAPSULSE,
        CYLINDER,
        CUSTOM
    };
    STRigidBody(){}
    STRigidBody(Transform* transform, RigidBodyShape shape){;}
    virtual void setMass(stReal mass) = 0;
    virtual void update(Transform* transform) = 0;

protected:
    Transform* m_transform;
};

#endif //SWINGTECH1_STRIGIDBODY_H
