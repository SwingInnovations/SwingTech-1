#ifndef SWINGTECH1_BULLETRIGIDBODYSHAPE_H
#define SWINGTECH1_BULLETRIGIDBODYSHAPE_H

#include <btBulletDynamicsCommon.h>
#include <c++/vector>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "../STRigidBody.h"

class BulletRigidBody : public STRigidBody{
public:
    explicit BulletRigidBody(Transform* transform, RigidBodyShape shape = BOX);
    btRigidBody*    getRigidBody();
    void setMass(stReal mass) override;
    stReal getMass()const override;
    void update(Transform* transform) override;
private:
    btCollisionShape* m_collisionShape;
    btRigidBody*      m_rigidBody;
};


#endif //SWINGTECH1_BULLETRIGIDBODYSHAPE_H
