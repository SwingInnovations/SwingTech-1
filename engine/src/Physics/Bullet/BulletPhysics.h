#ifndef SWINGTECH1_BULLETPHYSICS_H
#define SWINGTECH1_BULLETPHYSICS_H

#include "../STPhysics.h"

#include <btBulletDynamicsCommon.h>

class btDiscreteDynamicsWorld;

class BulletPhysics : public STPhysics{
public:
    BulletPhysics();
    void init() override ;
    void init(STPhysics::PhysicsEngine engineMode) override;
    void update(stUint delta) override;
    void setGravity(stReal gravity) override;
    void dispose() override;

    //Bullet Physics Specific Functions
    void addRigidBody();
    void clearScene();
private:
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btBroadphaseInterface*           m_broadphase;
    btConstraintSolver*              m_solver;
    btCollisionDispatcher*           m_dispatcher;
    btDiscreteDynamicsWorld*         m_dynamicsWorld;
};


#endif //SWINGTECH1_BULLETPHYSICS_H
