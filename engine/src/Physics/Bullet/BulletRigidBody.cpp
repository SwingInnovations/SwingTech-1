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

BulletRigidBody::BulletRigidBody(Transform *transform, STRigidBody::RigidBodyShape shape,
                                 std::vector<stReal> &dimensions) {
    m_transform = transform;
//    if(transform->getEntity()->get<STAABBComponent>() == nullptr){
//        std::cerr << "Error, STAABBComponent needed. Forgot to initialize?" << std::endl;
//        return;
//    }

    if(shape == AUTO){
        auto knownBounds = transform->getEntity()->get<STAABBComponent>()->getBoundingBox();
        auto knownExtents = knownBounds->getExtants();
        m_collisionShape = new btBoxShape({knownExtents.getX(), knownExtents.getY(), knownExtents.getZ()});
    }else if(shape == BOX){
        m_collisionShape = new btBoxShape({dimensions[0], dimensions[1], dimensions[2]});
    }else if(shape == STATIC_PLANE){
        m_collisionShape = new btStaticPlaneShape({dimensions[0], dimensions[1], dimensions[2]}, dimensions[3]);
    }else if(shape == SPHERE){
        m_collisionShape = new btSphereShape(dimensions[0]);
    }else if(shape == CAPSULE_X) {
        m_collisionShape = new btCapsuleShapeX(dimensions[0], dimensions[1]);
    }else if(shape == CAPSULE_Y){
        m_collisionShape = new btCapsuleShape(dimensions[0], dimensions[1]);
    }else if(shape == CAPSULE_Z){
        m_collisionShape = new btCapsuleShapeZ(dimensions[0], dimensions[1]);
    }else if(shape == CYLINDER){
        //TODO IMplement this
    }
    m_Mass = 10.0f;
    btVector3 localInertia(0, 0, 0);
    m_collisionShape->calculateLocalInertia(m_Mass, localInertia);
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    btRigidBody::btRigidBodyConstructionInfo ctInfo((btScalar)m_Mass, motionState, m_collisionShape, localInertia);

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
    btQuaternion quat;
    quat.setEulerZYX(toRadian(rot.getZ()), toRadian(rot.getY()), toRadian(rot.getX()));
    btTransform initTransform;
    initTransform.setOrigin(btVector3(trans.getX(), trans.getY(), trans.getZ()));
    initTransform.setRotation(quat);
    m_rigidBody->setWorldTransform(initTransform);
    m_rigidBody->getMotionState()->setWorldTransform(initTransform);
    m_rigidBody->clearForces();
}

void BulletRigidBody::applyImpulseForce(Vector3D vector) {
    m_ImpulseForce = vector;
    m_rigidBody->applyCentralImpulse({vector.getX(), vector.getY(), vector.getZ()});
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

void BulletRigidBody::applyTorqueImpulse(Vector3D torque) {
    m_rigidBody->applyTorqueImpulse({torque.getX(), torque.getY(), torque.getZ()});
}

void BulletRigidBody::applyTorque(Vector3D torque) {
    m_rigidBody->applyTorque({torque.getX(), torque.getY(), torque.getZ()});
}

void BulletRigidBody::setLinearVelocity(Vector3D lVec) {
    m_rigidBody->setLinearVelocity({lVec.getX(), lVec.getY(), lVec.getZ()});
}

void BulletRigidBody::setAngularVelocity(Vector3D aVec) {
    m_rigidBody->setAngularVelocity({aVec.getX(), aVec.getY(), aVec.getZ()});
}

Vector3D BulletRigidBody::getTotalForce() const {
    auto ret = m_rigidBody->getTotalForce();
    return {ret.getX(), ret.getY(), ret.getZ()};
}

Vector3D BulletRigidBody::getTorqueForce() const {
    auto ret = m_rigidBody->getTotalTorque();
    return {ret.getX(), ret.getY(), ret.getZ()};
}

Vector3D BulletRigidBody::getLinearVelocity() const {
    auto ret = m_rigidBody->getLinearVelocity();
    return { ret.getX(), ret.getY(), ret.getZ() };
}

Vector3D BulletRigidBody::getAngularVelocity() const {
    auto ret = m_rigidBody->getAngularVelocity();
    return {ret.getX(), ret.getY(), ret.getZ()};
}

void BulletRigidBody::save(std::ofstream &out) {
    out.write((char*)&m_Mass, sizeof(stReal));
    m_gravity.save(out);
    m_Linear.save(out);
    m_Angular.save(out);
    m_ImpulseForce.save(out);
}

void BulletRigidBody::load(std::ifstream &in) {
    in.read((char*)&m_Mass, sizeof(stReal));
    m_gravity.load(in);
    m_Linear.load(in);
    m_Angular.load(in);
    m_ImpulseForce.load(in);
}

BulletRigidBody::~BulletRigidBody() {
    if(m_rigidBody->getMotionState()){
        delete m_rigidBody->getMotionState();
    }
    delete m_rigidBody->getCollisionShape();
    delete m_rigidBody;
}

btCollisionShape *BulletRigidBody::getCollisionShape() {
    return m_collisionShape;
}

void BulletRigidBody::clearUserPointer() {
    m_rigidBody->setUserPointer(nullptr);
}




