#include "STButton.h"
#include "../STFontMetrics.h"
#include "../../Entity/Components/STRectBoundsComponent.h"
#include "STPanel.h"

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
    stInt width = 0, height  = 0;
    STFontMetrics::bounds(m_text, m_fontSize, m_font, &width, &height);
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(0, 0, width, height, STGraphics::YUp));
    buttonType = PUSH;
    m_Panel = new STPanel(0, 0, width, height);
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
    m_Panel = new STPanel(x, y, width, height);
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
    m_Panel = new STPanel(x, y, width, height);
}

void STButton::update(STGame *window) {
    if(get<STRectBoundsComponent>()->bounds()->contains(window->getInput()->getMouseCoords())){
        if(inputEvents != 0)invokeInputEvent(this);
    }
}

void STButton::draw(STGraphics *grphx) {
    if(m_visible){
        m_Panel->draw(grphx);
        grphx->drawText(m_position, m_text, m_fontSize, &m_fontColor.color);
    }
}

void STButton::inputEvent(std::function<void(STEntity*)> function) {
    inputEvents = function;
}

void STButton::invokeInputEvent(STEntity *entity) {
    this->inputEvents(entity);
}

void STButton::setIndex(stUint value) {
    m_index = value;
}

void STButton::setPosition(const Vector2<stReal> &position) {
    m_position = position;
    auto rect = get<STRectBoundsComponent>();
    if(rect != nullptr){
        stReal width = rect->bounds()->getWidth();
        stReal height = rect->bounds()->getHeight();
        stReal y = abs((stInt)m_position.getY() - STGame::RES_HEIGHT) - height;
        m_Panel->reset((stInt)m_position.getX(), (stInt)m_position.getY(), width, height);
        rect->reset(m_position.getX(), y, width, height);
    }
}
