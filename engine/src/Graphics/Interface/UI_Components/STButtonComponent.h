#ifndef SWINGTECH1_STBUTTONCOMPONENT_H
#define SWINGTECH1_STBUTTONCOMPONENT_H

#include "../../../Entity/Components/STComponent.h"

#include <functional>

class STEntity;

class STButtonComponent : public STComponent{
public:
    std::function<void (STEntity*)> OnClick = 0;
    void update(){
        if(isClicked){
            if(OnClick != 0) OnClick(this);
        }
    }
    void draw(){

    }
private:
    bool isClicked;
};

#endif //SWINGTECH1_STBUTTONCOMPONENT_H
