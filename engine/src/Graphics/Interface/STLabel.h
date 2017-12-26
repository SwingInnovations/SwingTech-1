#ifndef WAHOO_STLABEL_H
#define WAHOO_STLABEL_H

#include <functional>

#include "STInterWidget.h"
#include "../../Math/STCore.h"
#include "STPanel.h"

class STLabel : public STInterWidget {
public:
    STLabel();
    STLabel(stReal x, stReal y, std::string text);
    virtual void update(STGame *window);
    void hoverEvent(std::function<void (STEntity*, STGame*)> hoverEvent);
    void draw(STGraphics* grphx);
    STPanel* getPanel(){ return m_Panel; }
private:
    void invokeHoverEvent(STEntity*, STGame*);

    std::function<void (STEntity*, STGame*)> hoverEvents = 0;
    STPanel* m_Panel;
};


#endif //WAHOO_STLABEL_H
