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
    m_Mass = 10.0f;
    btVector3 localInertia(0, 0, 0);
    m_collisionShape->calculateLocalInertia(m_Mass, localInertia);
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    btRigidBody::btRigidBodyConstructionInfo ctInfo(m_Mass, motionState, m_collisionShape, localInertia);

    m_rigidBody = new btRigidBody(ctInfo);
    m_rigidBody->setUserPointer(((void*)transform->getEntity()));
}


btRigidBody *BulletRigidBody::getRigidBody() {
    return m_rigidBody;
}

void BulletRigidBody::setMass(stReal mass) {
    m_Mass = mass;
    btVector3 localInertia;
    m_rigidBody->getCollisionShape()->calculateLocalInertia(m_Mass, localInertia);
    m_rigidBody->setMassProps(m_Mass, localInertia);
}

float BulletRigidBody::getMass() const {
    return m_Mass;
}

void BulletRigidBody::update(Transform *transform) {

}

void BulletRigidBody::setGravity(Vector3D gravity) {
    m_gravity = gravity;
    m_rigidBody->setGravity(btVector3(gravity.getX(), gravity.getY(), gravity.getZ()));
}

void BulletRigidBody::setLinearFactor(Vector3D vector) {
    m_Linear = vector;
    m_rigidBody->setLinearFactor(btVector3(vector.getX(), vector.getY(), vector.getZ()));
}

void BulletRigidBody::setAngularFactor(Vector3D vector) {
    m_Angular = vector;
    m_rigidBody->setAngularFactor(btVector3(vector.getX(), vector.getY(), vector.getZ()));
}

void BulletRigidBody::updateTransform() {
    auto trans = m_transform->getTranslate();
    auto rot = m_transform->getRotate();
    btTransform initTransform;
    initTransform.setOrigin(btVector3(trans.getX(), trans.getY(), trans.getZ()));
    initTransform.setRotation(btQuaternion(rot.getX(), rot.getY(), rot.getZ()));
    m_rigidBody->setWorldTransform(initTransform);
    m_rigidBody->getMotionState()->setWorldTransform(initTransform);
    m_rigidBody->clearForces();
}

void BulletRigidBody::applyImpulseForce(Vector3D vector) {
    m_ImpulseForce = vector;
    m_rigidBody->applyCentralImpulse({vector.getX(), vector.getY(), vector.getZ()});
    //m_rigidBody->setLinearVelocity({vector.getX(), vector.getY(), vector.getZ()});
}

void BulletRigidBody::setActive(bool status) {
    m_rigidBody->activate(status);
}

void BulletRigidBody::setDamping(stReal v1, stReal v2) {
    m_rigidBody->setDamping(v1, v2);
}

void BulletRigidBody::applyGravity() {
    m_rigidBody->applyGravity();
}

void BulletRigidBody::setRestitution(float value) {
    m_rigidBody->setRestitution(value);
}

void BulletRigidBody::clearForces() {
    m_rigidBody->clearForces();
}

