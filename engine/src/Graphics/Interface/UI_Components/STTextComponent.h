#ifndef SWINGTECH1_STTEXTCOMPONENT_H
#define SWINGTECH1_STTEXTCOMPONENT_H

#include "../../../Entity/Components/STComponent.h"

class STTextComponent : public STComponent{
public:
    void setText(const std::string& text){ this->text = text; }
    const std::string getText()const{ return  text; }
private:
    std::string text;
};

#endif //SWINGTECH1_STTEXTCOMPONENT_H
