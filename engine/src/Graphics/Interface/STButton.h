#ifndef SWINGTECH1_STBUTTON_H
#define SWINGTECH1_STBUTTON_H

#include <c++/functional>
#include "STInterWidget.h"

class STButton : public STInterWidget{
public:
    STButton();
    STButton(const std::string& text);
    STButton(stReal x, stReal y, std::string text);
    void update(STGame* window) override;
    void draw(STGraphics* grphx) override;
    void inputEvent(std::function<void(STEntity*, STGame*)>);
private:
    void invokeInputEvent(STEntity*, STGame*);
    std::function<void(STEntity*, STGame*)> inputEvents = 0;
};


#endif //SWINGTECH1_STBUTTON_H
