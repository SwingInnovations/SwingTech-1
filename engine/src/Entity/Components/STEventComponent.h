#ifndef WAHOO_STEVENTCOMPONENT_H
#define WAHOO_STEVENTCOMPONENT_H

#include <functional>

#include <map>
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
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
    void setOther(STEntity* other);
    template<class Archive> void serialize(Archive& ar){
        ar(m_Events);
    }
private:
    std::map<std::string, std::function<void(STEntity*, STEntity*)>> m_Events;
    STEntity* other;
    std::string m_currentEvent;
};
#endif //WAHOO_STEVENTCOMPONENT_H
