#ifndef SWINGTECH1_STPHYSICS_H
#define SWINGTECH1_STPHYSICS_H

#include "../Math/STCore.h"

class STScene;
/**
 * Base class for initializing physics.
 */
class STPhysics{
public:
    enum PhysicsEngine : unsigned char{
        NONE = 0,
        BULLET = 1
    };

    explicit STPhysics();

    virtual void init() = 0;
    virtual void init(PhysicsEngine engine);
    virtual void update(stUint delta)  = 0;
    virtual void setGravity(stReal gravity) = 0;
    virtual void dispose() = 0;
    inline PhysicsEngine getPhysicsEngineMode() const{ return m_physicsEngine; }
protected:
    STScene* m_scene;
    PhysicsEngine  m_physicsEngine;
};

#endif //SWINGTECH1_STPHYSICS_H
