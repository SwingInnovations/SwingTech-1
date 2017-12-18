#ifndef SWINGTECH1_BULLETPHYSICS_H
#define SWINGTECH1_BULLETPHYSICS_H

#include "../STPhysics.h"

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

    void clearScene();
private:
    std::vector<btRigidBody*>       m_rigidBodyPool;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btBroadphaseInterface*           m_broadphase;
    btConstraintSolver*              m_solver;
    btCollisionDispatcher*           m_dispatcher;
    btDiscreteDynamicsWorld*         m_dynamicsWorld;
};


#endif //SWINGTECH1_BULLETPHYSICS_H
