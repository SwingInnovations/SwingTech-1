#include "BulletRigidBody.h"
#include "../../Entity/Transform.h"
#include "../../Entity/STEntity.h"
#include "../../Entity/Components/STAABBComponent.h"

BulletRigidBody::BulletRigidBody(Transform *transform, STRigidBody::RigidBodyShape shape) : STRigidBody(transform,
                                                                                                        shape) {
    m_transform = transform;
    if(transform->getEntity()->get<STAABBComponent>() == nullptr){
        std::cerr << "Error, STAABBComponent needed. Forgot to initialize?" << std::endl;
        return;
    }
    auto knownBoundingBox = transform->getEntity()->get<STAABBComponent>()->getBoundingBox();
    auto knownExtants = knownBoundingBox->getExtants();
    if(shape == BOX){
        m_collisionShape = new btBoxShape(btVector3(knownExtants.getX(), knownExtants.getY(), knownExtants.getZ()));
    }
    btVector3 localInertia(0, 0, 0);
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo ctInfo(m_Mass, motionState, m_collisionShape, localInertia);

    m_rigidBody = new btRigidBody(ctInfo);
    m_rigidBody->setUserPointer(((void*)transform->getEntity()));
}


btRigidBody *BulletRigidBody::getRigidBody() {
    return m_rigidBody;
}

void BulletRigidBody::setMass(stReal mass) {

}

float BulletRigidBody::getMass() const {
    return m_Mass;
}

void BulletRigidBody::update(Transform *transform) {

}

