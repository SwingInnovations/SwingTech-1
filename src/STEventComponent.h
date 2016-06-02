#ifndef WAHOO_STEVENTCOMPONENT_H
#define WAHOO_STEVENTCOMPONENT_H

#include <c++/functional>
#include "STComponent.h"

class STEventComponent : public STComponent{
public:
    enum Event_State{
        DEFAULT,
        HIT,
        INTERSECT
    };

    STEventComponent();
    ~STEventComponent();

    void update(STEntity*, STGame*, int);
    void draw();

    void setEventState(Event_State eState){ event_state = eState; }

    void hitEvent(std::function<void (STEntity*)> hitFunction);
    void intersectEvent(std::function<void (STEntity*)> intersectFunction);
    void inputEvent(std::function< void (STEntity*, Input*) > inputFunction);
    void updateEvent(std::function<void (STEntity*, STGame*) > updateFunction);

private:
    void invokeInputEvent(STEntity*, Input*);
    void invokeHitEvent(STEntity*);
    void invokeIntersectEvent(STEntity*);
    void invokeUpdateEvent(STEntity*, STGame*);

    std::function<void (STEntity*)> hitEvents = 0;
    std::function<void (STEntity*)> intersectEvents = 0;
    std::function<void (STEntity*, Input*)> inputEvents = 0;
    std::function<void (STEntity*, STGame*)> updateEvents = 0;
    Event_State event_state;
};


#endif //WAHOO_STEVENTCOMPONENT_H
