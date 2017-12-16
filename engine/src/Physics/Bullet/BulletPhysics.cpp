#include "BulletPhysics.h"
#include <iostream>

void BulletPhysics::init() {
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_broadphase = new btDbvtBroadphase();
    m_solver = new btSequentialImpulseConstraintSolver;
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
}

void BulletPhysics::update(stUint delta) {
    if(m_dynamicsWorld){
        m_dynamicsWorld->stepSimulation(delta);
    }
}

void BulletPhysics::setGravity(stReal gravity) {

}

void BulletPhysics::dispose() {
    //TODO Cleanup bullet stuff here.
}

BulletPhysics::BulletPhysics() {

}

void BulletPhysics::init(STPhysics::PhysicsEngine engineMode) {
    m_physicsEngine = engineMode;
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_broadphase = new btDbvtBroadphase();
    m_solver = new btSequentialImpulseConstraintSolver;
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    if(m_dynamicsWorld){
        std::cout << "Successfully built Bullet!" << std::endl;
    }
}
