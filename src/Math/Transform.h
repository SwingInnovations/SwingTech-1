#ifndef WAHOO_TRANSFORM_H
#define WAHOO_TRANSFORM_H

#include <iostream>

#include "STech_Core.h"
#include "Matrix.h"
#include "Vector.h"


class Transform{
public:
    Transform(){
        translate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
        rotate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
        scale = Vector3<stReal>(1.0f, 1.0f, 1.0f);
    }

    Transform(Vector3<stReal>& translate, Vector3<stReal>& rotate, Vector3<stReal> scale){
        this->translate = translate;
        this->rotate = rotate;
        this->scale = scale;
    }

    void setTranslate(Vector3<stReal>& vec){ this->translate = vec; }
    void setTranslateX(stReal _x){ this->translate.setX(_x); }
    void setTranslateY(stReal _y){ this->translate.setY(_y); }
    void setTranslateZ(stReal _z){ this->translate.setZ(_z); }

    void setRotate(Vector3<stReal>& vec){ this->rotate = vec; }
    void setRotateX(stReal _x){ this->rotate.setX(_x); }
    void setRotateY(stReal _y){ this->rotate.setY(_y); }
    void setRotateZ(stReal _z){ this->rotate.setZ(_z); }

    void setScale(Vector3<stReal>& vec){ this->scale = vec; }
    void setScaleX(stReal _x){ this->scale.setX(_x); }
    void setScaleY(stReal _y){ this->scale.setY(_y); }
    void setScaleZ(stReal _z){ this->scale.setZ(_z); }

    const Matrix4f getModel(){
        Matrix4f trans, rot, scaleMat, rotX, rotY, rotZ;
        trans.initTranslation(translate);
        rot.initRotate(rotate);
        scaleMat.initScale(scale);

        Matrix4f ret;
        ret = scaleMat * rot * trans;
        return ret;
    }

    template<typename T> Vector3<T> getTranslate()const{ return Vector3<T>((T)translate.getX(), (T)translate.getY(), (T)translate.getZ()); }
    template<typename T> Vector3<T> getRotate()const{ return Vector3<T>( (T)rotate.getX(), (T)rotate.getY(), (T)rotate.getZ() ); }
    template<typename T> Vector3<T> getScale()const{ return Vector3<T>( (T)scale.getX(), (T)scale.getY(), (T)scale.getZ() ); }
private:
    Vector3<stReal> translate;
    Vector3<stReal> rotate;
    Vector3<stReal> scale;
};

#endif //WAHOO_TRANSFORM_H
