#ifndef SWINGTECH1_BULLETRIGIDBODYSHAPE_H
#define SWINGTECH1_BULLETRIGIDBODYSHAPE_H

#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "../STRigidBody.h"
#include "../../Math/Vector.h"

class STEntity;

class BulletRigidBody : public STRigidBody{
public:
    BulletRigidBody(Transform* transform, RigidBodyShape shape = BOX);
    BulletRigidBody(Transform* transform, RigidBodyShape shape, std::vector<stReal>& dimensions);
    btRigidBody*    getRigidBody();

    void applyGravity() override ;
    void applyImpulseForce(Vector3D) override;
    void applyTorqueImpulse(Vector3D) override;
    void applyTorque(Vector3D) override;

    void setMass(stReal mass) override;
    void setGravity(Vector3D gravity) override;
    void setActive(bool) override;
    void setLinearFactor(Vector3D) override;
    void setAngularFactor(Vector3D) override;
    void setLinearVelocity(Vector3D) override ;
    void setAngularVelocity(Vector3D) override ;

    void setDamping(stReal, stReal) override;
    void setRestitution(stReal) override;
    void update(Transform* transform) override;

    void updateTransform() override;
    void clearForces() override;

    stReal getMass()const override;
    Vector3D getTotalForce() const override ;
    Vector3D getTorqueForce() const override ;
    Vector3D getLinearVelocity() const override ;
    Vector3D getAngularVelocity() const override;
private:
    btCollisionShape* m_collisionShape;
    btRigidBody*      m_rigidBody;
};


#endif //SWINGTECH1_BULLETRIGIDBODYSHAPE_H
