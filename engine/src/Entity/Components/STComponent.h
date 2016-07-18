#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "../../STGame.h"

class STEntity;

class STComponent {
public:
    virtual void update(STEntity*, STGame*) = 0; //Refer to self and the game
    virtual void draw(){ }
    virtual ~STComponent(){}
};


#endif //WAHOO_STCOMPONENT_H
