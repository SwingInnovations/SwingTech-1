#include "STButton.h"
#include "../STFontMetrics.h"
#include "../../Entity/Components/STRectBoundsComponent.h"

class STGraphics;

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
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(0, 0, width, height, STGraphics::YUp));
    buttonType = PUSH;
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
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height, STGraphics::getYUpSetting()));
    buttonType = PUSH;
}

STButton::STButton(stReal x, stReal y, std::string text, STButton::ButtonType type) {
    m_text = text;
    m_position.set(x, y);
    m_fontColor.set(WHITE);
    m_fontSize = 36;
    m_font = "fonts/arial.ttf";
    int width = 0, height = 0;
    m_visible = true;
    STFontMetrics::bounds(m_text, m_fontSize, m_font, &width, &height);
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height, STGraphics::getYUpSetting()));
    buttonType = type;
}

void STButton::update(STGame *window) {
    if(get<STRectBoundsComponent>()->bounds()->contains(window->getInput()->getMouseCoords<stReal>())){
        if(inputEvents != 0)invokeInputEvent(this);
    }
}

void STButton::draw(STGraphics *grphx) {
    if(m_visible) grphx->drawText(m_position, m_text, m_fontSize, &m_fontColor.color);
}

void STButton::inputEvent(std::function<void(STEntity*)> function) {
    inputEvents = function;
}

void STButton::invokeInputEvent(STEntity *entity) {
    this->inputEvents(entity);
}

void STButton::setIndex(unsigned stInt value) {
    index = value;
}
