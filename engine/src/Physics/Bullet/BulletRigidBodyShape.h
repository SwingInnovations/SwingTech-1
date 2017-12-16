#ifndef SWINGTECH1_BULLETRIGIDBODYSHAPE_H
#define SWINGTECH1_BULLETRIGIDBODYSHAPE_H

#include "../STRigidBody.h"

class BulletRigidBodyShape : public STRigidBody{
public:
    BulletRigidBodyShape(Transform* transform, RigidBodyShape shape);
};


#endif //SWINGTECH1_BULLETRIGIDBODYSHAPE_H
