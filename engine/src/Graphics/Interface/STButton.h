#ifndef SWINGTECH1_STBUTTON_H
#define SWINGTECH1_STBUTTON_H

#include <c++/functional>
#include "STInterWidget.h"
#include "../STGraphics.h"

class STButton : public STInterWidget{
public:
    enum ButtonType{
        PUSH = 0,
        TOOL = 1,
        RADIO = 2
    };

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
