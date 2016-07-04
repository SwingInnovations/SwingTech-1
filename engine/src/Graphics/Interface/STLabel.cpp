#include "STLabel.h"
#include "../../Entity/Components/STRectBoundsComponent.h"
#include "../STFontMetrics.h"

STLabel::STLabel() {

}

STLabel::STLabel(stReal x, stReal y, std::string text) {
    m_text = text;
    m_position.set(x, y);
    m_fontColor.set(0);
    m_fontSize = 36;
    m_font = "fonts/arial.ttf";
    int width = 0, height = 0;
    m_visible = true;
    y -= STGame::RES_HEIGHT;
    STFontMetrics::bounds(m_text, m_fontSize, m_font, &width, &height);
    y = abs(y) - height;
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height));
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
    if(m_visible) grphx->drawText(m_position, m_text, m_fontSize, &m_fontColor.color);
}

void STLabel::invokeHoverEvent(STEntity *entity, STGame *game) {
    if(hoverEvents != 0)this->hoverEvents(entity, game);
}

void STLabel::hoverEvent(std::function<void(STEntity *, STGame *)> hoverEvent) {
    hoverEvents = hoverEvent;
}
