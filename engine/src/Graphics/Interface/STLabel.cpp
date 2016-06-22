#include "STLabel.h"
#include "../../STRectBoundsComponent.h"

STLabel::STLabel() {

}

STLabel::STLabel(stReal x, stReal y, stReal width, stReal height) {
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height));
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



