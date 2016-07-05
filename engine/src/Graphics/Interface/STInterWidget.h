#ifndef WAHOO_STINTERWIDGET_H
#define WAHOO_STINTERWIDGET_H

#include "../../STGame.h"
#include "../../Entity/STEntity.h"
#include "../STColor.h"
#include "../../Entity/Components/STRectBoundsComponent.h"

class STInterWidget : public STEntity{
public:
    enum Event{
        Hover,
        Click,
        None
    };

    STInterWidget(){
        m_type = GUI;
    }

    void setText(const std::string& text){ m_text = text; }
    void setFontColor(const STColor& color){ m_fontColor = color; }
    void setFontSize(unsigned int size){ m_fontSize = size; }
    void setBackgroundColor(const STColor& color){ m_backgroundColor = color; }
    void setForegroundColor(const STColor& color){ m_foregroundColor = color; }

    void setPadding(unsigned int padding){ m_padding = padding; }
    void setPosition(const Vector2<stReal> position){
        m_position = position;
        auto rect = get<STRectBoundsComponent>();
        if(rect != nullptr){
            stReal width = rect->bounds()->getWidth();
            stReal height = rect->bounds()->getHeight();
            stReal y = abs((int)m_position.getY() - STGame::RES_HEIGHT) - height;
            rect->reset(m_position.getX(), y, width, height);
        }
    }

    // TODO - Move these to Event Component
//    virtual void keyEvent() = 0;
//    virtual void mouseEvent() = 0;
//    virtual void clickEvent() = 0;
//    virtual void pressEvent() = 0;
//    virtual void releaseEvent() = 0;
protected:
    std::string m_text;
    std::string m_font;

    unsigned int m_fontSize;
    unsigned int m_padding;

    STColor m_fontColor;
    STColor m_backgroundColor;
    STColor m_foregroundColor;

    Event eventType;
    Vector2<stReal> m_position;
};

#endif //WAHOO_STINTERWIDGET_H
