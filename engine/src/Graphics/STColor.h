#ifndef WAHOO_STCOLOR_H
#define WAHOO_STCOLOR_H

#include "../Math/STCore.h"
#include "../Math/Vector.h"

enum {
    RED = 0,
    MAGENTA = 1,
    YELLOW = 2,
    GREEN = 3,
    CYAN = 4,
    BLUE = 5,
    BLACK = 6,
    WHITE = 7
};

struct STColor{
    STColor() {
        color = Vector4<stReal>(1.0, 1.0f, 1.0f, 1.0f); //Creates blank white color
    }

    STColor(int col){
        switch(col){
            case RED:
                color = Vector4<stReal>(1.0f, 0.0f, 0.0f, 1.0f);
            default:
                ;
        }
    }

    Vector4<stReal> color;
};

#endif //WAHOO_STCOLOR_H
