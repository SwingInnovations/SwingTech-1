#include "STLabel.h"
#include "../../Entity/Components/STRectBoundsComponent.h"

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

STLabel::STLabel(stReal x, stReal y, std::string &text) {
    m_text = text;
    m_position.set(x, y);
    m_fontColor.set(BLACK);
}

void STLabel::draw(){

}