#include "ST3DPhysicsComponent.h"
#include "../STEntity.h"
#include "../../Physics/Bullet/BulletRigidBody.h"

ST3DPhysicsComponent::ST3DPhysicsComponent() {

}

STRigidBody *ST3DPhysicsComponent::getRigidBody() {
    return m_rigidBody;
}

void ST3DPhysicsComponent::init(STEntity *parent) {
    STComponent::init(parent);
    if(STGame::Get()->getPhysicsMode() == 1){
        m_rigidBody = new BulletRigidBody(parent->transform(), STRigidBody::BOX);
    }
}

void ST3DPhysicsComponent::setMass(const stReal mass) {
    m_rigidBody->setMass(mass);
}

void ST3DPhysicsComponent::update() {

}

void ST3DPhysicsComponent::dispose() {

}

ST3DPhysicsComponent::~ST3DPhysicsComponent() {
    delete m_rigidBody;
}

