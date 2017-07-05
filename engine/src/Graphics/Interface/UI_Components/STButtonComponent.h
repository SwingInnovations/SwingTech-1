#ifndef SWINGTECH1_STBUTTONCOMPONENT_H
#define SWINGTECH1_STBUTTONCOMPONENT_H

#include "../../../Entity/Components/STComponent.h"

#include <functional>

class STEntity;

class STButtonComponent : public STComponent{
public:
    enum BUTTON_TYPE : char{
        PUSH,
        CHECK
    };
    std::function<void (STEntity*)> OnClick = 0;
    void update(){

    }
    void draw(){

    }
private:
    BUTTON_TYPE m_buttonType;
    bool isChecked;
    bool isClicked;
};

#endif //SWINGTECH1_STBUTTONCOMPONENT_H
