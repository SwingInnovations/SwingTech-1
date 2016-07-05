#include "STButton.h"
#include "../STFontMetrics.h"
#include "../../Entity/Components/STRectBoundsComponent.h"

STButton::STButton() {

}

STButton::STButton(const std::string &text) {
    m_text =  text;
    m_position.set(0, 0);
    m_fontColor.set(WHITE);
    m_fontSize = 36;
    m_font = "fonts/arial.ttf";
    m_visible = true;
    int width = 0, height  = 0;
    STFontMetrics::bounds(m_text, m_fontSize, m_font, &width, &height);
    stReal y = STGame::RES_HEIGHT - height;
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(0, y, width, height));
}

STButton::STButton(stReal x, stReal y, std::string text) {
    m_text = text;
    m_position.set(x, y);
    m_fontColor.set(WHITE);
    m_fontSize = 36;
    m_font = "fonts/arial.ttf";
    int width = 0, height = 0;
    m_visible = true;
    STFontMetrics::bounds(m_text, m_fontSize, m_font, &width, &height);
    y = abs((int)y - STGame::RES_HEIGHT) - height;
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height));
}

void STButton::update(STGame *window) {
    if(get<STRectBoundsComponent>()->bounds()->contains(window->getInput()->getMouseCoords<stReal>())){
        if(inputEvents != 0)invokeInputEvent(this, window);
    }
}

void STButton::draw(STGraphics *grphx) {
    if(m_visible) grphx->drawText(m_position, m_text, m_fontSize, &m_fontColor.color);
}

void STButton::inputEvent(std::function<void(STEntity*, STGame*)> function) {
    inputEvents = function;
}

void STButton::invokeInputEvent(STEntity *entity, STGame *game) {
    this->inputEvents(entity, game);
}

