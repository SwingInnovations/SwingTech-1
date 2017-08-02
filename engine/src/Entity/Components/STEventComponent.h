#ifndef WAHOO_STEVENTCOMPONENT_H
#define WAHOO_STEVENTCOMPONENT_H

#if __linux__
#include <functional>
#else
#include <c++/functional>
#endif

#include <map>

#include "STComponent.h"

class STEventComponent : public STComponent{
public:

    STEventComponent();
    ~STEventComponent() override;

    void update() override;
    void draw() override;

    void setEvent(const std::string& event);
    void addEvent(std::string name, std::function<void(STEntity*, STEntity*)> newFunction);
    void updateEvent(std::string name, std::function<void(STEntity*, STEntity*)> alteredFunction);
private:

    std::map<std::string, std::function<void(STEntity*, STEntity*)>> m_Events;
    STEntity* other;
    std::string m_currentEvent;
};


#endif //WAHOO_STEVENTCOMPONENT_H
