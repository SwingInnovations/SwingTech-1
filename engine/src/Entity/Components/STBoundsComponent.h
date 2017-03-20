#ifndef SWINGTECH1_STBOUNDSCOMPONENT_H
#define SWINGTECH1_STBOUNDSCOMPONENT_H

#include "STComponent.h"

class STBoundsComponent : public STComponent{
public:
    virtual void adjustTransX(stReal x) = 0;
    virtual void adjustTransY(stReal y) = 0;
    virtual void adjustTransZ(stReal z) = 0;

    virtual void reconstructBounds() = 0;
    virtual bool contains(STEntity*) = 0;

};


#endif //SWINGTECH1_STBOUNDSCOMPONENT_H
