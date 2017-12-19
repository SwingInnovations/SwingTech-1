#ifndef SWINGTECH1_ST3DPHYSICSCOMPONENT_H
#define SWINGTECH1_ST3DPHYSICSCOMPONENT_H

#include "STComponent.h"
#include "../../Physics/STRigidBody.h"

class ST3DPhysicsComponent : public STComponent {
public:
    ST3DPhysicsComponent();
    ~ST3DPhysicsComponent();
    void init(STEntity* parent) override;
    STRigidBody* getRigidBody();
    void update();
    void dispose() override;
    void setMass(const stReal mass);
    void setGravity(Vector3D gravity);
    void setActive(bool);
    void toggleFreeze(bool);
    void updateTransform();
    void applyForce(Vector3D);
    void setDamping(stReal, stReal);
    void applyGravity();
    void setRestitution(stReal value);
private:
    STRigidBody* m_rigidBody;
};


#endif //SWINGTECH1_ST3DPHYSICSCOMPONENT_H
