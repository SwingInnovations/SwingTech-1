#ifndef SWINGTECH1_STPANEL_H
#define SWINGTECH1_STPANEL_H

#include "STInterWidget.h"

class STPanel : public STInterWidget{
public:
    STPanel();
    STPanel(int, int, int, int);
    void draw(STGraphics* grphx);
    inline void setColor(STColor color){
        this->m_baseColor = color;
        auto gfx = get<STRendererComponent>();
        if(gfx != nullptr) gfx->setShdrUniform("m_baseColor", m_baseColor.color);
    }

    STColor getColor()const{ return m_baseColor; }
    void reset(int x, int y, stReal w, stReal h);
private:
    STColor m_baseColor;
};


#endif //SWINGTECH1_STPANEL_H
