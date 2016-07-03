#ifndef WAHOO_STRECTBOUNDSCOMPONENT_H
#define WAHOO_STRECTBOUNDSCOMPONENT_H

#include "STComponent.h"
#include "../../Math/2D Bounds/BoundRect.h"

class STRectBoundsComponent : public STComponent {
public:
    STRectBoundsComponent(stReal _x, stReal _y, stReal _width, stReal _height);

    void update(STEntity* self, STGame* game, int);
    BoundRect* bounds(){ return rect; }
    std::string info();
private:
    BoundRect* rect;
};


#endif //WAHOO_STRECTBOUNDSCOMPONENT_H
