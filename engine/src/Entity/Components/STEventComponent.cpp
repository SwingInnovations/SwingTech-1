#include "STEventComponent.h"

STEventComponent::STEventComponent() {

}


void STEventComponent::draw() {
    STComponent::draw();
}


STEventComponent::~STEventComponent() {

}



void STEventComponent::intersectEvent(std::function<void(STEntity *)> intersectFunction) {
    intersectEvents = intersectFunction;
}

void STEventComponent::hitEvent(std::function<void(STEntity*, STEntity*)> hitFunction) {
    hitEvents = hitFunction;
}

void STEventComponent::invokeHitEvent(STEntity *entity, STEntity* stEntity) {
    if(hitEvents != 0) hitEvents(entity, stEntity);
}

void STEventComponent::invokeIntersectEvent(STEntity *entity) {
    if(intersectEvents != 0) this->intersectEvents(entity);
}

void STEventComponent::inputEvent(std::function<void(STEntity *)> inputFunction) {
    inputEvents = inputFunction;
}

void STEventComponent::invokeInputEvent(STEntity *entity) {
    if(inputEvents != 0) this->inputEvents(entity);
}

void STEventComponent::updateEvent(std::function<void(STEntity *entity)> updateFunction) {
    updateEvents = updateFunction;
}

void STEventComponent::invokeUpdateEvent(STEntity *entity) {
    if(updateEvents != 0) updateEvents(entity);
}


void STEventComponent::triggerHitEvent(STEntity *entity) {
    other = entity;
    event_state = HIT;
}

void STEventComponent::update() {
    switch(event_state){
        case HIT:
            invokeHitEvent(this->getParent(), other);
            event_state = DEFAULT;
            break;
        case INTERSECT:
            invokeIntersectEvent(this->getParent());
            event_state = DEFAULT;
            break;
        case DEFAULT:
            break;
        default:
            break;
    }
    invokeInputEvent(this->getParent());
    invokeUpdateEvent(this->getParent());
    if(other != nullptr) other = nullptr;

    for(auto event : m_Events){
        if(m_currentEvent == event.first) event.second(getParent(), other);
    }
}

void STEventComponent::addEvent(std::string name, std::function<void(STEntity*, STEntity*)> newFunction) {
    m_Events.insert(std::pair<std::string, std::function<void(STEntity*, STEntity*)>>(name, newFunction));
}

void STEventComponent::triggerEvent(std::string eventName) {
    other = nullptr;
    m_currentEvent = eventName;
}

void STEventComponent::triggerEvent(std::string eventName, STEntity *other) {
    m_currentEvent = eventName;
    this->other = other;
}
