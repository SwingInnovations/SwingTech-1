#include "STPhysics.h"
#include "Bullet/BulletPhysics.h"

STPhysics::STPhysics() {

}


void STPhysics::init(STPhysics::PhysicsEngine engine) {
    m_physicsEngine = engine;
}

/***
 * Returns a list of STEntity from raycast test.
 * @param start Starting Position
 * @param end End Position
 * @return List of STEntity from raytest. List is empty if nothing was found.
 */
STList<STEntity *> STPhysics::Raycast(Vector3D start, Vector3D end) const {
    if(m_physicsEngine == BULLET){
        return ((BulletPhysics*)this)->RaycaseHelper(start, end);
    }
    return STList<STEntity*>();
}
