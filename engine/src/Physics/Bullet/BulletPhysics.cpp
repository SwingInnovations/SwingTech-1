#include "BulletPhysics.h"
#include "../../Application/STSceneManager.h"
#include "../../Entity/Components/ST3DPhysicsComponent.h"
#include "BulletRigidBody.h"
#include <iostream>

BulletPhysics::BulletPhysics() {

}

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
        for(stUint i = 0; i < m_dynamicsWorld->getDispatcher()->getNumManifolds(); i++){
            auto collision = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
            auto body0 = collision->getBody0();
            auto body1 = collision->getBody1();
            auto gameObject = ((STActor*)body0->getUserPointer());
        }
    }
}

void BulletPhysics::setGravity(stReal gravity) {
    if(m_dynamicsWorld){
        m_dynamicsWorld->setGravity(btVector3(0, -gravity, 0));
    }
}

void BulletPhysics::dispose() {
    //TODO Cleanup bullet stuff here.
}



void BulletPhysics::init(STPhysics::PhysicsEngine engineMode) {
    m_physicsEngine = engineMode;
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_broadphase = new btDbvtBroadphase();
    m_solver = new btSequentialImpulseConstraintSolver;
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    if(m_dynamicsWorld){
        std::cout << "Using Bullet Physics Engine" << std::endl;
    }
}

void BulletPhysics::clearScene() {
    m_dynamicsWorld->getCollisionObjectArray().clear();
}

void BulletPhysics::initScene(STScene *scene) {
    m_scene = scene;
    for(auto actor : scene->getActors()){
        auto physComponent = actor->get<ST3DPhysicsComponent>();
        if(physComponent != nullptr){
            m_dynamicsWorld->addRigidBody(dynamic_cast<BulletRigidBody*>(actor->get<ST3DPhysicsComponent>())->getRigidBody());
        }
    }
}

BulletPhysics::~BulletPhysics() {
    delete m_dynamicsWorld;
    delete m_solver;
    delete m_broadphase;
    delete m_dispatcher;
    delete m_collisionConfiguration;
}
