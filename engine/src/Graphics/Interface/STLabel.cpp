#include "STLabel.h"
#include "../../Entity/Components/STRectBoundsComponent.h"
#include "../STFontMetrics.h"
#include "STPanel.h"

STLabel::STLabel() {

}

STLabel::STLabel(stReal x, stReal y, std::string text) {
    m_text = text;
    m_position.set(x, y);
    m_fontColor.set(WHITE);
    m_fontSize = 36;
    m_font = "fonts/arial.ttf";
    int width = 0, height = 0;
    m_visible = true;
    STFontMetrics::bounds(m_text, m_fontSize, m_font, &width, &height);
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height, STGraphics::YUp));
    m_Panel = new STPanel(x, y, width, height);
}

void STLabel::update(STGame *window) {
    auto input = window->getInput();
    auto bounds = get<STRectBoundsComponent>()->bounds();
    if(bounds->contains(input->getMouseCoords<stReal>()) ){
        invokeHoverEvent(this, window);
    }
    eventType = None;
}

void STLabel::draw(STGraphics* grphx){
    if(m_visible) {
        m_Panel->draw(grphx);
        grphx->drawText(m_position, m_text, m_fontSize, &m_fontColor.color);
    }
}

void STLabel::invokeHoverEvent(STEntity *entity, STGame *game) {
    if(hoverEvents != 0)this->hoverEvents(entity, game);
}

void STLabel::hoverEvent(std::function<void(STEntity *, STGame *)> hoverEvent) {
    hoverEvents = hoverEvent;
}
