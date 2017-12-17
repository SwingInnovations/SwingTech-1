#include "ST3DPhysicsComponent.h"
#include "../STEntity.h"
#include "../../Physics/Bullet/BulletRigidBody.h"

STRigidBody *ST3DPhysicsComponent::getRigidBody() {
    return m_rigidBody;
}

void ST3DPhysicsComponent::init(STEntity *parent) {
    STComponent::init(parent);

}
