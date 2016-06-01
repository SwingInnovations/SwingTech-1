#include "STEventComponent.h"

STEventComponent::STEventComponent() {

}

void STEventComponent::update(STEntity *entity, STGame *game, int delta) {

    switch(event_state){
        case HIT:
            invokeHitEvent(entity);
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
}


void STEventComponent::draw() {
    STComponent::draw();
}


STEventComponent::~STEventComponent() {

}

void STEventComponent::hitEvent(std::function<void(STEntity *)> hitFunction) {
    hitEvents = hitFunction;
}

void STEventComponent::intersectEvent(std::function<void(STEntity *)> intersectFunction) {
    intersectEvents = intersectFunction;
}

void STEventComponent::invokeHitEvent(STEntity *entity) {
    if(hitEvents != 0) this->hitEvents(entity);
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

