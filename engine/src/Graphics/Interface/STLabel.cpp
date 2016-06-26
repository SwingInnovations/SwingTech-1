#include "STLabel.h"
#include "../../STRectBoundsComponent.h"

STLabel::STLabel() {

}


void STLabel::update(STGame *window) {
    auto input = window->getInput();
    auto bounds = get<STRectBoundsComponent>()->bounds();
    if(bounds->contains(input->getMouseCoords<stReal>()) ){
        //TODO Hover Event
        if(input->isMousePressed(0)){
            //TODO Implement mouse function
        }
    }
    eventType = None;
}



