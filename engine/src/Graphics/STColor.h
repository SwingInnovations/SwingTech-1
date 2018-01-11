#ifndef WAHOO_STCOLOR_H
#define WAHOO_STCOLOR_H

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>

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

    STColor(stReal r, stReal g, stReal b, stReal a){
        color = Vector4<stReal>(r, g, b, a);
    }

    explicit STColor(int col){
        switch(col){
            case RED:
                color = Vector4<stReal>(1.0f, 0.0f, 0.0f, 1.0f);
                break;
            case MAGENTA:
                color = Vector4<stReal>(1.0f, 0.0f, 1.0f, 1.0f);
                break;
            case YELLOW:
                color = Vector4<stReal>(1.0f, 1.0f, 0.0f, 1.0f);
                break;
            case GREEN:
                color = Vector4<stReal>(0.0f, 1.0f, 0.0f, 1.0f);
                break;
            case CYAN:
                color = Vector4<stReal>(0.0f, 1.0f, 1.0f, 1.0f);
                break;
            case BLUE:
                color = Vector4<stReal>(0.0f, 0.0f, 1.0f, 1.0f);
                break;
            case BLACK:
                color = Vector4<stReal>(0.0f, 0.0f, 0.0f, 1.0f);
                break;
            case WHITE:
                color = Vector4<stReal>(1.0f, 1.0f, 1.0f, 1.0f);
            default:
                ;
        }
    }

    /**
     * Sets Color
     * @param col
     */
    inline void set(Vector3<stReal> col){
        color = Vector4<stReal>(col, 1.0);
    }

    /**
     * Sets Color
     * @param col
     */
    inline void set(Vector4<stReal> col){
        color = col;
    }

    inline void set(const int col){
        switch(col){
            case RED:
                color = Vector4<stReal>(1.0f, 0.0f, 0.0f, 1.0f);
                break;
            case MAGENTA:
                color = Vector4<stReal>(1.0f, 0.0f, 1.0f, 1.0f);
                break;
            case YELLOW:
                color = Vector4<stReal>(1.0f, 1.0f, 0.0f, 1.0f);
                break;
            case GREEN:
                color = Vector4<stReal>(0.0f, 1.0f, 0.0f, 1.0f);
                break;
            case CYAN:
                color = Vector4<stReal>(0.0f, 1.0f, 1.0f, 1.0f);
                break;
            case BLUE:
                color = Vector4<stReal>(0.0f, 0.0f, 1.0f, 1.0f);
                break;
            case BLACK:
                color = Vector4<stReal>(0.0f, 0.0f, 0.0f, 1.0f);
                break;
            case WHITE:
                color = Vector4<stReal>(1.0f, 1.0f, 1.0f, 1.0f);
            default:
                ;
        }
    }

    /**
     * Sets Red value of color
     * @param value Red Color
     */
    inline void setRed(const stReal value){
        auto val = value;
        if(value > 1.0f) val /= 255.0f;
        color.setX(val);
    }

    /**
     * Sets Green value of Color
     * @param value Green Color
     */
    inline void setGreen(const stReal value){
        auto val = value;
        if(value > 1.0f) val /= 255.0f;
        color.setY(val);
    }

    /**
     * Sets Blue value of Color
     * @param value Blue Color
     */
    inline void setBlue(const stReal value){
        auto val = value;
        if(value > 1.0f) val /= 255.0f;
        color.setZ(val);
    }

    template<class Archive> void serialize(Archive& ar){
        ar(color);
    }

    Vector4<stReal> color;
};

#endif //WAHOO_STCOLOR_H
