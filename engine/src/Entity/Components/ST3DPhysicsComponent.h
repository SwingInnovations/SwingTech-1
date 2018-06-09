#ifndef SWINGTECH1_ST3DPHYSICSCOMPONENT_H
#define SWINGTECH1_ST3DPHYSICSCOMPONENT_H

#include "STComponent.h"
#include "../../Physics/STRigidBody.h"


class ST3DPhysicsComponent : public STComponent {
public:
    ST3DPhysicsComponent();
    ST3DPhysicsComponent(STRigidBody::RigidBodyShape bodyShape, std::vector<stReal> dimensions);
    ~ST3DPhysicsComponent() override ;
    void init(std::shared_ptr<STEntity>& parent) override;

    /**
     * Allows for scripting access.
     * @param state
     */
    void initScriptingFunctions(sol::state& state) override ;

	/**
	*	Returns the rigid body
	*	@returns RigidBody Abstracted Class
	*/
    STRigidBody* getRigidBody();

    /**
     * Applies gravity to Object
     */
    void applyGravity();
    /**
     * Applies force to object based off Axis
     */
    void applyForce(Vector3D);

	/**
	 * Sets the mass of the rigid body. 
	 */
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
	
	/**
	 * Toggles the rigid body as active.   
	 * @param flag 
	 */
    void toggleFreeze(bool);

	/**
	 * Enforces the rigid body is updated. 
	 */
    void updateTransform();

    void update() override ;
    void dispose() override;

    void save(std::ofstream& out) override;
    void load(std::ifstream& in) override;

private:
    STRigidBody* m_rigidBody;
    STRigidBody::RigidBodyShape m_initShape;
    std::vector<stReal> m_dimensions;
};

#endif //SWINGTECH1_ST3DPHYSICSCOMPONENT_H
