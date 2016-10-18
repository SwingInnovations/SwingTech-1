#ifndef WAHOO_STLABEL_H
#define WAHOO_STLABEL_H

#include <c++/functional>
#include "STInterWidget.h"
#include "../../Math/STCore.h"

class STLabel : public STInterWidget {
public:
    STLabel();
    STLabel(stReal x, stReal y, std::string text);
    virtual void update(STGame *window);
    void hoverEvent(std::function<void (STEntity*, STGame*)> hoverEvent);
    void draw(STGraphics* grphx);
private:
    void invokeHoverEvent(STEntity*, STGame*);

    std::function<void (STEntity*, STGame*)> hoverEvents = 0;

};


#endif //WAHOO_STLABEL_H
