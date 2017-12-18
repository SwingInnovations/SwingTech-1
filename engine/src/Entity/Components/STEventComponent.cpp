#include "STEventComponent.h"

STEventComponent::STEventComponent() {

}

void STEventComponent::update() {
    for(auto event : m_Events){
        if(event.first == m_currentEvent){
            event.second(this->m_entity, other);
            m_currentEvent = "";
        }

        if(event.first == "update"){
            event.second(this->m_entity, other);
        }
    }
}

void STEventComponent::draw() {
    STComponent::draw();
}


STEventComponent::~STEventComponent() {

}


void STEventComponent::addEvent(std::string name, std::function<void(STEntity*, STEntity*)> newFunction) {
    m_Events.insert(std::pair<std::string, std::function<void(STEntity*, STEntity*)>>(name, newFunction));
}

void STEventComponent::setEvent(const std::string& newEvent) {
    m_currentEvent = newEvent;
}

void STEventComponent::updateEvent(std::string name, std::function<void(STEntity *, STEntity *)> alteredFunction) {
    if(m_Events.count(name) > 0) {
        m_Events.at(name) = alteredFunction;
        return;
    }
    addEvent(name, alteredFunction);
}

void STEventComponent::setResultants(std::vector<STEntity*>& resultants, stUint numResultants) {
    this->resultants = resultants;
    this->numResultants = numResultants;
}
