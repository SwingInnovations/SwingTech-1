#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "STGame.h"

class STComponent {
public:
    virtual void update(STGame *, int){  }
    virtual void draw(){  }
    virtual ~STComponent(){}
};


#endif //WAHOO_STCOMPONENT_H
