#ifndef SWINGTECH1_BULLETPHYSICS_H
#define SWINGTECH1_BULLETPHYSICS_H

#include "../STPhysics.h"
#include "../STRigidBody.h"

#include <btBulletDynamicsCommon.h>
#include <vector>

class btDiscreteDynamicsWorld;

class BulletPhysics : public STPhysics{
public:
    BulletPhysics();
    ~BulletPhysics();
    void init() override ;
    void init(STPhysics::PhysicsEngine engineMode) override;
    void initScene(STScene* scene) override ;
    void update(stUint delta) override;
    void setGravity(stReal gravity) override;
    void dispose() override;
    void removeFromPhysicsWorld(STRigidBody* rigidBody) override;
    void clearScene();
    STList<STEntity*> RaycaseHelper(Vector3D start, Vector3D end) override ;
    void addToPhysicsWorld(STRigidBody* rigidBody) override;
private:
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btBroadphaseInterface*           m_broadphase;
    btConstraintSolver*              m_solver;
    btCollisionDispatcher*           m_dispatcher;
    btDiscreteDynamicsWorld*         m_dynamicsWorld;
};


#endif //SWINGTECH1_BULLETPHYSICS_H
