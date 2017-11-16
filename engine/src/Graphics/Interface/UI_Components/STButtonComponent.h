#ifndef SWINGTECH1_STBUTTONCOMPONENT_H
#define SWINGTECH1_STBUTTONCOMPONENT_H

#include "../../../Entity/Components/STComponent.h"
#include "../../../Entity/Components/STEventComponent.h"

#include <functional>

class STEntity;

class STButtonComponent : public STComponent{
public:
    enum BUTTON_TYPE : char{
        PUSH,
        CHECK
    };

    void update() override {
        if(m_entity != nullptr){
            //Should never hit here but whatever
            m_entity->get<STEventComponent>();
        }
    }

    void draw(){

    }

private:
    BUTTON_TYPE m_buttonType;
    bool isChecked;
    bool isCheckeable;
    bool isClicked;
};

#endif //SWINGTECH1_STBUTTONCOMPONENT_H
