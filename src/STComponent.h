#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include "STechWindow.h"

class STComponent {
public:
    virtual void update(STechWindow*, int){  }
    virtual void draw(){  }
    virtual ~STComponent(){}
};


#endif //WAHOO_STCOMPONENT_H
