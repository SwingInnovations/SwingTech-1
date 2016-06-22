#ifndef WAHOO_BOUNDRECT_H
#define WAHOO_BOUNDRECT_H

#include "BoundShape.h"

class BoundRect : public BoundShape{
public:
    BoundRect(){
        points.push_back(0);
        points.push_back(0);
        points.push_back(1);
        points.push_back(1);

        m_iterations = 1;
    }

    BoundRect(stReal x, stReal y, stReal width, stReal height){
        m_iterations = 1;

        points.push_back(x);
        points.push_back(y);
        points.push_back(width);
        points.push_back(height);
    }


    virtual bool contains(const BoundShape &other){
        return false;
    }

    virtual bool contains(const Vector2<stReal> &cursor){
        stReal x = points.at(0);
        stReal y = points.at(1);
        stReal w = points.at(2);
        stReal h = points.at(3);

        return cursor.getX() >= x &&
        cursor.getX() <= x + w &&
        cursor.getY() >= y &&
        cursor.getY() <= y + h;
    }
};

#endif //WAHOO_BOUNDRECT_H