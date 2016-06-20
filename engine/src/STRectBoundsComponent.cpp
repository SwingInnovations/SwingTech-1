//
// Created by NDanq on 6/16/2016.
//

#include "STRectBoundsComponent.h"

STRectBoundsComponent::STRectBoundsComponent(stReal _x, stReal _y, stReal _width, stReal _height) {
    rect = new BoundRect(_x, _y, _width, _height);
}

// Unused, but implemented so it doesn't break the engine.
void STRectBoundsComponent::update(STEntity *self, STGame *game, int i) {

}

