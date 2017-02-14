#ifndef WAHOO_STEVENTCOMPONENT_H
#define WAHOO_STEVENTCOMPONENT_H

#if __linux__
#include <functional>
#else
#include <c++/functional>
#endif

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

    void update();
    void draw();

    void triggerHitEvent(STEntity*);

    inline void setEventState(Event_State eState){ event_state = eState; }
    void hitEvent(std::function<void (STEntity*, STEntity*)>);
    void intersectEvent(std::function<void (STEntity*)> intersectFunction);
    void inputEvent(std::function< void (STEntity*) > inputFunction);
    void updateEvent(std::function<void (STEntity*) > updateFunction);

    void set(Event_State state){ event_state = state; }

private:
    void invokeHitEvent(STEntity*, STEntity*);
    void invokeInputEvent(STEntity*);
    void invokeIntersectEvent(STEntity*);
    void invokeUpdateEvent(STEntity*);

    std::function<void (STEntity*, STEntity*)> hitEvents;
    std::function<void (STEntity*)> intersectEvents = 0;
    std::function<void (STEntity*)> inputEvents = 0;
    std::function<void (STEntity*)> updateEvents = 0;
    Event_State event_state;
    STEntity* other;
};


#endif //WAHOO_STEVENTCOMPONENT_H
