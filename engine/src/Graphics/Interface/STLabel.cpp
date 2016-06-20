#include "STLabel.h"
#include "../../STRectBoundsComponent.h"

STLabel::STLabel() {

}

STLabel::STLabel(stReal x, stReal y, stReal width, stReal height) {
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height));
}


void STLabel::update(STGame *window) {
    STEntity::update(window);
}



