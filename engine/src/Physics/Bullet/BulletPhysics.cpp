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
    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void BulletPhysics::update(stUint delta) {
    if(m_dynamicsWorld){
        m_dynamicsWorld->stepSimulation(delta);
        for(stUint i = 0; i < m_dynamicsWorld->getDispatcher()->getNumManifolds(); i++){
            auto collision = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
            auto gameObject = ((STEntity*)collision->getBody0()->getUserPointer());
            auto otherObject = ((STEntity*)collision->getBody1()->getUserPointer());
            std::vector<STEntity*> result;
            result.push_back(otherObject);
            auto eventComp = gameObject->get<STEventComponent>();
            eventComp->setResultants(result, 0);
            eventComp->setEvent("onCollision");
        }

        for(int i = 0, L = m_dynamicsWorld->getNumCollisionObjects(); i < L; i++){
            auto collisionObj = m_dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* rigidBody = btRigidBody::upcast(collisionObj);
            btTransform transform;
            if(rigidBody->getMotionState() != nullptr){
                rigidBody->getMotionState()->getWorldTransform(transform);
            }else{
                transform = rigidBody->getWorldTransform();
            }
            auto entityTransform = ((STEntity*)rigidBody->getUserPointer())->transform();
            entityTransform->setTranslate(Vector3D(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()));
        }

//        for(auto rigidBody : m_rigidBodyPool){
//            auto rigidEnt = ((STEntity*)rigidBody->getUserPointer());
//            auto transform = ((STEntity*)rigidBody->getUserPointer())->transform();
//            btScalar* m = new btScalar[16];
//            btScalar rX, rY, rZ;
//            std::cout << rigidBody->getInvMass() << std::endl;
//            rigidBody->getCenterOfMassTransform().getOpenGLMatrix(m);
//            rigidBody->getCenterOfMassTransform().getRotation().getEulerZYX(rZ, rY, rX);
//            transform->setTranslate(Vector3D(m[12], m[13], m[14]));
//            transform->setRotate(Vector3D(rX, rY, rZ));
//            delete m;
//        }
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
    m_rigidBodyPool.clear();
}

void BulletPhysics::initScene(STScene *scene) {
    m_scene = scene;
    for(auto actor : scene->getActors()){
        auto physComponent = actor->get<ST3DPhysicsComponent>();
        if(physComponent != nullptr){
            auto rigidBody = ((BulletRigidBody*)physComponent->getRigidBody())->getRigidBody();
            m_dynamicsWorld->addRigidBody(rigidBody);
            m_rigidBodyPool.push_back(rigidBody);
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
