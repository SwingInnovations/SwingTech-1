#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "../../../include/sol.hpp"
#include "../../Application/STGame.h"

class STEntity;
/**
 * Parent of componenet can always be referred to by accessing the parent.
 * Game can be accessed via the STGame Singleton
 */
class STComponent {
public:
    virtual void init(STEntity* newParent){this->m_entity = newParent;}      //This will actually initialize anything dependent on the m_entity pointer.
    /**
     * Initializes stuff
     */
    virtual void initScriptingFunctions(sol::state m_script){;}
    virtual void update() = 0;
    virtual void draw(){ }
    /**
     * @brief Independently called to clear contents of component.
     */
    virtual void dispose(){}
    virtual ~STComponent(){}

    inline void setParent(STEntity* parent){ this->m_entity = parent; }
    STEntity* getParent(){ return this->m_entity; }

protected:
    STEntity* m_entity;
};


#endif //WAHOO_STCOMPONENT_H
