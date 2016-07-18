//
// Created by NDanq on 6/16/2016.
//

#include "STRectBoundsComponent.h"

STRectBoundsComponent::STRectBoundsComponent(stReal _x, stReal _y, stReal _width, stReal _height) {
    rect = new BoundRect(_x, _y, _width, _height);
}

STRectBoundsComponent::STRectBoundsComponent(stReal _x, stReal _y, stReal _width, stReal _height, bool YUpFlag) {
    stReal y;
    if(!YUpFlag){
        y = abs(_y - STGame::RES_HEIGHT) - _height;
    }else y = _y;

    rect = new BoundRect(_x, y, _width, _height);
}

std::string STRectBoundsComponent::info() {
    return rect->info();
}

void STRectBoundsComponent::reset(const stReal x, const stReal y, const stReal w, const stReal h) {
    rect->reset(x, y, w, h);
}

void STRectBoundsComponent::update(STEntity *self, STGame *game) {

}
