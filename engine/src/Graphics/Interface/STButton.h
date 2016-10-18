#ifndef SWINGTECH1_STBUTTON_H
#define SWINGTECH1_STBUTTON_H

#include <c++/functional>
#include "STInterWidget.h"
#include "../STGraphics.h"
#include "STButtonGroup.h"
#include "STMenu.h"
#include "STPanel.h"

class STButtonGroup;

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
    STButton(stReal x, stReal y, std::string text, ButtonType type);

    void update(STGame* window);
    void draw(STGraphics* grphx) override;
    void inputEvent(std::function<void(STEntity*)>);

    inline void setToggle(bool val){
        m_toggled = val;
        parent->toggleGroup(m_index);
    }

    inline void setMenu(STMenu* menu){ this->m_menu = menu; }
    inline bool isToggled(){ return m_toggled; }
    void setIndex(unsigned int);
    inline void toggle(){ m_toggled =! m_toggled; }

    STPanel* getPanel(){ return m_Panel; }
    virtual void setPosition(const Vector2<stReal>& position);
private:
    void invokeInputEvent(STEntity*);
    std::function<void(STEntity*)> inputEvents = 0;
    ButtonType buttonType;
    bool m_toggled;
    STButtonGroup* parent = NULL;
    STMenu* m_menu;
    stUint m_index;
    STPanel* m_Panel;
};


#endif //SWINGTECH1_STBUTTON_H
