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
    /**
     * Available Shapes.
     */
    enum RigidBodyShape : unsigned char{
        AUTO,
        BOX,
        STATIC_PLANE,
        SPHERE,
        CAPSULE,
        CYLINDER,
        CUSTOM
    };
    STRigidBody(){}
    STRigidBody(Transform* transform, RigidBodyShape shape){;}
    STRigidBody(Transform* transform, RigidBodyShape shape, std::vector<stReal>& dimensions){;}
    virtual ~STRigidBody() {}
    /**
     * Sets Gravity of Rigid Body
     * @param gravity
     */
    virtual void setGravity(Vector3D gravity) = 0;
    virtual void applyGravity() = 0;

    /**
     * Applies Impulse force
     * @param force
     */
    virtual void applyImpulseForce(Vector3D force) = 0;

    /**
     * Applies impulse torque
     * @param torque
     */
    virtual void applyTorqueImpulse(Vector3D torque) = 0;

    /**
     * Applies Torque
     * @param torque
     */
    virtual void applyTorque(Vector3D torque) = 0;

    /**
     * Sets Mass of rigid body
     * @param mass
     */
    virtual void setMass(stReal mass) = 0;

    /**
     * Toggles Active state of rigid body
     * @param flag
     */
    virtual void setActive(bool flag) = 0;

    /**
     * Sets Linear Factor
     * @param value
     */
    virtual void setLinearFactor(Vector3D value) = 0;

    /**
     * Sets Linear Velocity
     * @param value
     */
    virtual void setLinearVelocity(Vector3D value) = 0;

    /**
     * Sets Angular Factor
     * @param value
     */
    virtual void setAngularFactor(Vector3D value) = 0;

    /**
     * Sets Angular Velocity
     * @param value
     */
    virtual void setAngularVelocity(Vector3D value) = 0;

    virtual void setDamping(stReal, stReal) = 0;
    /**
     * Sets 'Bounciness' factor of rigid body
     * @param value
     */
    virtual void setRestitution(stReal value) = 0;

    /**
     * Clears forces on rigid body
     */
    virtual void clearForces() = 0;

    virtual void save(std::ofstream& out) = 0;
    virtual void load(std::ifstream& in) = 0;

    [[deprecated]]
    virtual void update(Transform* transform) = 0;
    /**
     * Enforces Update transform;
     */
    virtual void updateTransform() = 0;

    virtual stReal getMass()const = 0;
    virtual Vector3D getTotalForce() const = 0;
    virtual Vector3D getTorqueForce()const  = 0;
    virtual Vector3D getLinearVelocity()const  = 0;
    virtual Vector3D getAngularVelocity() const = 0;
protected:
    Transform* m_transform;
    stReal m_Mass = 1.0f;
    Vector3D m_gravity;
    Vector3D m_Linear;
    Vector3D m_Angular;
    Vector3D m_ImpulseForce;
};

#endif //SWINGTECH1_STRIGIDBODY_H
