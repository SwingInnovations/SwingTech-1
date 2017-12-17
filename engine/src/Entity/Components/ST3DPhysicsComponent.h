#ifndef SWINGTECH1_ST3DPHYSICSCOMPONENT_H
#define SWINGTECH1_ST3DPHYSICSCOMPONENT_H

#include "STComponent.h"
#include "../../Physics/STRigidBody.h"

class ST3DPhysicsComponent : public STComponent {
public:
    ST3DPhysicsComponent();
    void init(STEntity* parent) override;
    STRigidBody* getRigidBody();
private:
    STRigidBody* m_rigidBody;
};


#endif //SWINGTECH1_ST3DPHYSICSCOMPONENT_H
