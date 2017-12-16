#include "BulletRigidBodyShape.h"

BulletRigidBodyShape::BulletRigidBodyShape(Transform *transform, STRigidBody::RigidBodyShape shape) {
    m_transform = transform;
    switch(shape){
        case BOX:
            //TODO Create somesort of box based off Extents
            break;
        default:
            ;
    }
}
