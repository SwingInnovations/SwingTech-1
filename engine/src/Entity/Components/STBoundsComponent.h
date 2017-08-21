#ifndef SWINGTECH1_STBOUNDSCOMPONENT_H
#define SWINGTECH1_STBOUNDSCOMPONENT_H

#include "STComponent.h"

class STBoundsComponent : public STComponent{
public:
    virtual void calculateBounds() = 0;
    virtual bool contains(STEntity*) = 0;
    virtual bool intersects(STEntity*) = 0;
};


#endif //SWINGTECH1_STBOUNDSCOMPONENT_H
