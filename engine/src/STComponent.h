#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "STGame.h"

class STEntity;

class STComponent {
public:
    virtual void update(STGame *, int){  }
    virtual void update(STEntity*, STGame*, int) = 0;
    virtual void update(STEntity*, STGame*){ ; } //Refer to self and the game
    virtual void draw(){  }
    virtual ~STComponent(){}
};


#endif //WAHOO_STCOMPONENT_H
