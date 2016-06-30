#include "STLabel.h"
#include "../../Entity/Components/STRectBoundsComponent.h"

STLabel::STLabel() {

}

STLabel::STLabel(stReal x, stReal y, std::string &text) {
    m_text = text;
    m_position.set(x, y);
    m_fontColor.set(BLACK);
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

void STLabel::draw(STGraphics* grphx){
    if(m_visible) grphx->drawText(m_position, m_text, m_fontSize, m_fontColor);
}