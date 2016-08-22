#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "../../STGame.h"

class STEntity;

//TODO Replace the update function from refering to self to update()
/*
 * Parent of componenet can always be refered to by accesing the parent.
 * Game can be accessed via the STGame Singleton
 */

class STComponent {
public:
    virtual void update() = 0;
    virtual void draw(){ }
    virtual ~STComponent(){}

    inline void setParent(STEntity* parent){ this->parent = parent; }
    STEntity* getParent(){ return this->parent; }

protected:
    STEntity* parent;
};


#endif //WAHOO_STCOMPONENT_H
