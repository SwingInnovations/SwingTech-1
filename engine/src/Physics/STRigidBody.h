#ifndef SWINGTECH1_STRIGIDBODY_H
#define SWINGTECH1_STRIGIDBODY_H

#include "../Math/STCore.h"
#include "../Math/Vector.h"

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
    virtual void setGravity(Vector3D gravity) = 0;
    virtual void applyGravity() = 0;
    virtual stReal getMass()const = 0;
    virtual void update(Transform* transform) = 0;
    virtual void setActive(bool) = 0;
    virtual void setLinearFactor(Vector3D) = 0;
    virtual void setAngularFactor(Vector3D) = 0;
    virtual void updateTransform() = 0;
    virtual void applyImpulseForce(Vector3D) = 0;
    virtual void setDamping(stReal, stReal) = 0;
    virtual void setRestitution(stReal) = 0;
    virtual void clearForces() = 0;
protected:
    Transform* m_transform;
    stReal m_Mass = 1.0f;
    Vector3D m_gravity;
    Vector3D m_Linear;
    Vector3D m_Angular;
    Vector3D m_ImpulseForce;
};

#endif //SWINGTECH1_STRIGIDBODY_H
