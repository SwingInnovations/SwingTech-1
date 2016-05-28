#include "STEventComponent.h"

STEventComponent::STEventComponent() {
    isHit = false;
}

void STEventComponent::update(STEntity *entity, STGame *game, int delta) {
    if(isHit){
        invokeOnHit();
        isHit = false;
    }
}


void STEventComponent::draw() {
    STComponent::draw();
}


void STEventComponent::invokeOnHit() {
    this->onHitFunc();
}

void STEventComponent::onHit(std::function<void(void)> func) {
    this->onHitFunc = func;
}
