#ifndef SWINGTECH1_STBUTTONGROUP_H
#define SWINGTECH1_STBUTTONGROUP_H

//Button group handler for radio buttons

#include "STButton.h"

class STButtonGroup {
public:
    STButtonGroup();
    void add(STButton*);
    void toggleGroup(int index);
private:
    std::vector<STButton*> buttons;
};


#endif //SWINGTECH1_STBUTTONGROUP_H
