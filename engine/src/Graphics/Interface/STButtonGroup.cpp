#include "STButtonGroup.h"

STButtonGroup::STButtonGroup() {

}

void STButtonGroup::add(STButton *button) {
    button->setIndex((unsigned int)buttons.size() + 1);
    buttons.push_back(button);
}

void STButtonGroup::toggleGroup(int index) {
    for(unsigned int i = 0, L = (unsigned int)buttons.size(); i < L; i++){
        if(i != index) buttons.at(i)->toggle();
    }
}
