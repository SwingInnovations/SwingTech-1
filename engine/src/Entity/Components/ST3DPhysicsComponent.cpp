#include "ST3DPhysicsComponent.h"
#include "../STEntity.h"
#include "../../Physics/Bullet/BulletRigidBody.h"

ST3DPhysicsComponent::ST3DPhysicsComponent(){
    m_initShape = STRigidBody::RigidBodyShape::BOX;
}

ST3DPhysicsComponent::ST3DPhysicsComponent(STRigidBody::RigidBodyShape bodyShape, std::vector<stReal> dimensions) {
    m_initShape = bodyShape;
    for(auto val : dimensions){
        m_dimensions.push_back(val);
    }
}

STRigidBody *ST3DPhysicsComponent::getRigidBody() {
    return m_rigidBody;
}

void ST3DPhysicsComponent::init(STEntity *parent) {
    STComponent::init(parent);
    if(STGame::Get()->getPhysicsMode() == 1){
        m_rigidBody = new BulletRigidBody(parent->transform(), m_initShape, m_dimensions);
    }
}

void ST3DPhysicsComponent::setMass(stReal mass) {
    m_rigidBody->setMass(mass);
}

void ST3DPhysicsComponent::update() {

}

void ST3DPhysicsComponent::dispose() {

}

ST3DPhysicsComponent::~ST3DPhysicsComponent() {
    delete m_rigidBody;
}

void ST3DPhysicsComponent::setGravity(Vector3D gravity) {
    m_rigidBody->setGravity(gravity);
}

void ST3DPhysicsComponent::toggleFreeze(bool toggleFlag) {
    if(toggleFlag){
        m_rigidBody->setLinearFactor(Vector3D());
        m_rigidBody->setAngularFactor(Vector3D());
        m_rigidBody->clearForces();
        return;
    }
    m_rigidBody->setLinearFactor(Vector3D(1, 1, 1));
    m_rigidBody->setAngularFactor(Vector3D(1, 1, 1));
}

void ST3DPhysicsComponent::updateTransform() {
    m_rigidBody->updateTransform();
}

void ST3DPhysicsComponent::applyForce(Vector3D vector) {
    m_rigidBody->applyImpulseForce(vector);
}

void ST3DPhysicsComponent::setActive(bool flag) {
    m_rigidBody->setActive(flag);
}

void ST3DPhysicsComponent::setDamping(float v1, float v2) {
    m_rigidBody->setDamping(v1, v2);
}

void ST3DPhysicsComponent::applyGravity() {
    m_rigidBody->applyGravity();
}

void ST3DPhysicsComponent::setRestitution(stReal value) {
    m_rigidBody->setRestitution(value);
}

void ST3DPhysicsComponent::initScriptingFunctions(sol::state &state) {
    state.set_function("get3DPhysicsComponent", [](STEntity* self){
        return self->get<ST3DPhysicsComponent>();
    });
    state.new_simple_usertype<ST3DPhysicsComponent>("ST3DPhysicsComponent",
                                "applyGravity", &ST3DPhysicsComponent::applyGravity,
                                "applyForce", &ST3DPhysicsComponent::applyForce,
                                "setMass", &ST3DPhysicsComponent::setMass,
                                "setActive", &ST3DPhysicsComponent::setActive,
                                "setDamping", &ST3DPhysicsComponent::setDamping,
                                "setRestitution", &ST3DPhysicsComponent::setRestitution,
                                "toggleFreeze", &ST3DPhysicsComponent::toggleFreeze,
                                "updateTransform", &ST3DPhysicsComponent::updateTransform);
}


