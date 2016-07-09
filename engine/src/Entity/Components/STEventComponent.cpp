#include "STEventComponent.h"

STEventComponent::STEventComponent() {

}

void STEventComponent::update(STEntity *entity, STGame *game, int delta) {

    switch(event_state){
        case HIT:
            invokeHitEvent(entity, game, other);
            event_state = DEFAULT;
            break;
        case INTERSECT:
            invokeIntersectEvent(entity);
            event_state = DEFAULT;
            break;
        case DEFAULT:
            // Do Nothing;
            break;
        default:
            ;
    }

    invokeInputEvent(entity, game->getInput());
    invokeUpdateEvent(entity, game);

    if(other != nullptr) other = nullptr;
}


void STEventComponent::draw() {
    STComponent::draw();
}


STEventComponent::~STEventComponent() {

}



void STEventComponent::intersectEvent(std::function<void(STEntity *)> intersectFunction) {
    intersectEvents = intersectFunction;
}

void STEventComponent::hitEvent(std::function<void(STEntity*, STGame*, STEntity*)> hitFunction) {
    hitEvents = hitFunction;
}

void STEventComponent::invokeHitEvent(STEntity *entity, STGame *game, STEntity *stEntity) {
    if(hitEvents != 0) hitEvents(entity, game, stEntity);
}

void STEventComponent::invokeIntersectEvent(STEntity *entity) {
    if(intersectEvents != 0) this->intersectEvents(entity);
}

void STEventComponent::inputEvent(std::function<void(STEntity *, Input *)> inputFunction) {
    inputEvents = inputFunction;
}

void STEventComponent::invokeInputEvent(STEntity *entity, Input *input) {
    if(inputEvents != 0) this->inputEvents(entity, input);
}

void STEventComponent::updateEvent(std::function<void(STEntity *entity, STGame* game)> updateFunction) {
    updateEvents = updateFunction;
}

void STEventComponent::invokeUpdateEvent(STEntity *entity, STGame* game) {
    if(updateEvents != 0) updateEvents(entity, game);
}


void STEventComponent::triggerHitEvent(STEntity *entity) {
    other = entity;
    event_state = HIT;
}