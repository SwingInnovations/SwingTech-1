#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "../../STGame.h"

class STEntity;
/**
 * Parent of componenet can always be referred to by accessing the parent.
 * Game can be accessed via the STGame Singleton
 */
class STComponent {
public:
    virtual void init(STEntity* newParent){this->parent = newParent;}      //This will actually initialize anything dependent on the parent pointer.
    virtual void update() = 0;
    virtual void draw(){ }
    virtual ~STComponent(){}

    inline void setParent(STEntity* parent){ this->parent = parent; }
    STEntity* getParent(){ return this->parent; }

protected:
    STEntity* parent;
};


#endif //WAHOO_STCOMPONENT_H
