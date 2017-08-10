#include "Transform.h"
#include "../Entity/STEntity.h"

Transform::Transform(STEntity *parent) {
    this->parent = parent;
    this->translate = Vector3<stReal>(0.f, 0.f, 0.f);
    rotate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
    scale = Vector3<stReal>(1.0f, 1.0f, 1.0f);
    localRotate = Euler<stReal>(0.0f, 0.0f, 0.0f);
    rotateMode = Global;
}

void Transform::setTranslate(Vector3<stReal> &vec) {
    this->translate = vec;
    if(parent != nullptr){
        if(parent->hasChildren()){
            for(auto child : parent->getChildren()){
                auto childPos = child->transform()->getTranslate();
                childPos = childPos + vec;
                child->transform()->setTranslate(childPos);
            }
        }
    }
}

void Transform::setTranslateX(stReal _x) {
    this->translate.setX(_x);
    if(parent != nullptr && parent->hasChildren()){
        for(auto child : parent->getChildren()){
            stReal cX = child->transform()->getTranslate().getX();
            cX += _x;
            child->transform()->setTranslateX(cX);
        }
    }
}

void Transform::setTranslateY(stReal _y) {
    this->translate.setY(_y);
    if(parent != nullptr && parent->hasChildren()){
        for(auto child : parent->getChildren()){
            stReal cY = child->transform()->getTranslate().getY() + _y;
            child->transform()->setTranslateY(cY);
        }
    }
}

void Transform::setTranslateZ(stReal _z) {
    this->translate.setZ(_z);
    if(parent != nullptr && parent->hasChildren()){
        for(auto child : parent->getChildren()){
            child->transform()->setTranslateZ(child->transform()->getTranslate().getZ() + _z);
        }
    }
}
