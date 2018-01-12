#ifndef SWINGTECH1_ST3DPHYSICSCOMPONENT_H
#define SWINGTECH1_ST3DPHYSICSCOMPONENT_H

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "STComponent.h"
#include "../../Physics/STRigidBody.h"


class ST3DPhysicsComponent : public STComponent {
public:
    ST3DPhysicsComponent();
    ST3DPhysicsComponent(STRigidBody::RigidBodyShape bodyShape, std::vector<stReal> dimensions);
    ~ST3DPhysicsComponent();
    void init(std::shared_ptr<STEntity>& parent) override;
    /**
     * Allows for scripting access.
     * @param state
     */
    void initScriptingFunctions(sol::state& state) override ;

    STRigidBody* getRigidBody();

    /**
     * Applies gravity to Object
     */
    void applyGravity();
    /**
     * Applies force to object based off Axis
     */
    void applyForce(Vector3D);

    void setMass(stReal mass);

    /**
     * Sets the gravity parameter
     * @param gravity
     */
    void setGravity(Vector3D gravity);
    void setActive(bool);
    void setDamping(stReal, stReal);
    /**
     * Sets "Bounciness" of object
     * @param value
     */
    void setRestitution(stReal value);
    void toggleFreeze(bool);
    void updateTransform();

    void update() override ;
    void dispose() override;

    template<typename Archive> inline void serialize(Archive& ar){
        ar(m_initShape, m_dimensions);
    }
private:
    STRigidBody* m_rigidBody;
    STRigidBody::RigidBodyShape m_initShape;
    std::vector<stReal> m_dimensions;
};

#endif //SWINGTECH1_ST3DPHYSICSCOMPONENT_H
