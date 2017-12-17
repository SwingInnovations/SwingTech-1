#include "BulletRigidBody.h"
#include "../../Entity/Transform.h"

BulletRigidBody::BulletRigidBody(Transform *transform, STRigidBody::RigidBodyShape shape,
                                           std::vector<stReal> points) {
    m_transform = transform;
    switch(shape){
        case BOX:
            //TODO Create somesort of box based off Extents
            break;
        default:
            ;
    }
    btVector3 localInertia(0, 0, 0);
    m_rigidBody = new btRigidBody(m_Mass, nullptr, nullptr);
    m_rigidBody->setUserPointer(((void*)transform->getEntity()));
}

btRigidBody *BulletRigidBody::getRigidBody() {
    return m_rigidBody;
}
