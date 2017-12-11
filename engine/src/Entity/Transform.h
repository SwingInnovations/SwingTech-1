#ifndef WAHOO_TRANSFORM_H
#define WAHOO_TRANSFORM_H

#include <iostream>

#include "../../include/json11/json11.hpp"

#include "../Math/STCore.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "../Math/Euler.h"

class STEntity;

using namespace json11;

/**
 * @brief Hold Transformation Information.
 */
class Transform{
public:
    enum RotationMode: unsigned char {Global = 0, Local = 1};

    static Transform* FromJson(const std::string& jsonFile);
    static Transform* FromJson(const Json doc);

    explicit Transform(STEntity* parent);

    Transform(){
        parent = nullptr;
        translate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
        rotate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
        scale = Vector3<stReal>(1.0f, 1.0f, 1.0f);
        rotateMode = Global;
    }

    Transform(Vector3<stReal>& translate, Vector3<stReal>& rotate, Vector3<stReal> scale){
        parent = nullptr;
        this->translate = translate;
        this->rotate = rotate;
        this->scale = scale;
        rotateMode = Global;
    }

    void setTranslate(Vector3<stReal>& vec);
    void setTranslateX(stReal _x);
    void setTranslateY(stReal _y);
    void setTranslateZ(stReal _z);
    void setTranslate(stReal _value);

    void setRotate(Vector3<stReal>& vec);

    void setRotateX(stReal _x);

    void setRotateY(stReal _y);

    void setRotateZ(stReal _z);

    inline void setScale(Vector3<stReal>& vec){ this->scale = vec; }
    inline void setScaleX(stReal _x){ this->scale.setX(_x); }
    inline void setScaleY(stReal _y){ this->scale.setY(_y); }
    inline void setScaleZ(stReal _z){ this->scale.setZ(_z); }
    inline void setScale(stReal _value){
        setScaleX(_value);
        setScaleY(_value);
        setScaleZ(_value);
    }

    inline void setRotationMode(RotationMode rotMode){
        rotateMode = rotMode;
    }

    /**
     * Calculates the final transformation Matrix
     * @return Transformation Matrix
     */
    const Matrix4f getModel()const;

    inline std::string getInfo();

    inline Vector3<stReal> getTranslate()const{return translate; }
    inline Vector3<stReal> getRotate() const {return rotate;}
    inline Vector3<stReal> getScale() const {return scale;}

    Json to_json()const;

private:
    STEntity* parent;
    Vector3D translate;
    Vector3D rotate;
    Vector3<stReal> scale;
    RotationMode rotateMode;
};


#endif //WAHOO_TRANSFORM_H
