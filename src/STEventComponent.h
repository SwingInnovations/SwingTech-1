#ifndef WAHOO_STEVENTCOMPONENT_H
#define WAHOO_STEVENTCOMPONENT_H

#include <c++/functional>
#include "STComponent.h"

class STEventComponent : public STComponent{
public:
    STEventComponent();

    void update(STEntity*, STGame*, int);
    void draw();
    void onHit(std::function<void(void)> func);

    void setIsHit(bool isHit) {
        this->isHit = isHit;
    }

private:
    bool isHit;
    void invokeOnHit();

    std::function<void (void)> onHitFunc;
};


#endif //WAHOO_STEVENTCOMPONENT_H
