#ifndef WAHOO_STINTERWIDGET_H
#define WAHOO_STINTERWIDGET_H

#include "../../STGame.h"
#include "../../STEntity.h"
#include "../STColor.h"

class STInterWidget : public STEntity{
public:
    STInterWidget(){}

    STInterWidget(STEntity* parent){

    }

    void setText(const std::string& text){ m_text = text; }
    void setFontColor(STColor& color){ m_fontColor = color; }
    void setBackgroundColor(STColor& color){ m_backgroundColor = color; }
    void setForegroundColor(STColor& color){ m_foregroundColor = color; }

    void setVisible(bool val){ m_visible = val; }
    bool isVisible(){ return m_visible; }

    virtual void keyEvent() = 0;
    virtual void mouseEvent() = 0;
    virtual void clickEvent() = 0;
    virtual void pressEvent() = 0;
    virtual void releaseEvent() = 0;
protected:
    std::string m_text;
    STColor m_fontColor;
    STColor m_backgroundColor;
    STColor m_foregroundColor;
    bool m_visible;
};

#endif //WAHOO_STINTERWIDGET_H
