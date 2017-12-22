#ifndef SWINGTECH1_ST3DPHYSICSCOMPONENT_H
#define SWINGTECH1_ST3DPHYSICSCOMPONENT_H

#include "STComponent.h"
#include "../../Physics/STRigidBody.h"

class ST3DPhysicsComponent : public STComponent {
public:
    ST3DPhysicsComponent();
    ST3DPhysicsComponent(STRigidBody::RigidBodyShape bodyShape, std::vector<stReal> dimensions);
    ~ST3DPhysicsComponent();
    void init(STEntity* parent) override;
    STRigidBody* getRigidBody();

    /**
     * Applies gravity to Object
     */
    void applyGravity();
    /**
     * Applies force to object based off Axis
     */
    void applyForce(Vector3D);
    void dispose() override;
    void setMass(stReal mass);
    void setGravity(Vector3D gravity);
    void setActive(bool);
    void setDamping(stReal, stReal);
    /**
     * Sets "Bounciness" of object
     * @param value
     */
    void setRestitution(stReal value);
    void toggleFreeze(bool);
    void updateTransform();

    void update() override ;
private:
    STRigidBody* m_rigidBody;
    STRigidBody::RigidBodyShape m_initShape;
    std::vector<stReal> m_dimensions;
};


#endif //SWINGTECH1_ST3DPHYSICSCOMPONENT_H
