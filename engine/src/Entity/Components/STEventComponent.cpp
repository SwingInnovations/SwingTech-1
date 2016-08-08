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

void STEventComponent::update(STEntity *entity, STGame* game) {

    switch(event_state){
        case HIT:
            invokeHitEvent(entity, other);
            event_state = DEFAULT;
            break;
        case INTERSECT:
            invokeIntersectEvent(entity);
            event_state = DEFAULT;
            break;
        case DEFAULT:

            break;
        default:
            ;
    }

    invokeInputEvent(entity);
    invokeUpdateEvent(entity);

    if(other != nullptr) other = nullptr;
}
