#ifndef WAHOO_TRANSFORM_H
#define WAHOO_TRANSFORM_H

#include <iostream>

#include "STCore.h"
#include "Matrix.h"
#include "Vector.h"
#include "Euler.h"

class Transform{
public:
    enum RotationMode{Global = 0, Local = 1};

    Transform(){
        translate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
        rotate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
        scale = Vector3<stReal>(1.0f, 1.0f, 1.0f);
        localRotate = Euler<stReal>(0.0f, 0.0f, 0.0f);
        rotateMode = Global;
    }

    Transform(Vector3<stReal>& translate, Vector3<stReal>& rotate, Vector3<stReal> scale){
        this->translate = translate;
        this->rotate = rotate;
        this->scale = scale;
        localRotate = Euler<stReal>(0.0f, 0.0f, 0.0f);
        rotateMode = Global;
    }

    void setTranslate(Vector3<stReal>& vec){ this->translate = vec; }
    void setTranslateX(stReal _x){ this->translate.setX(_x); }
    void setTranslateY(stReal _y){ this->translate.setY(_y); }
    void setTranslateZ(stReal _z){ this->translate.setZ(_z); }
    void setTranslate(stReal _value){
        setTranslateX(_value);
        setTranslateY(_value);
        setTranslateZ(_value);
    }

    void setRotate(Vector3<stReal>& vec){
        if(rotateMode == Global) this->rotate = vec;
        else this->localRotate.set(vec);
    }

    void setRotateX(stReal _x){
        if(rotateMode == Global) this->rotate.setX(_x);
        else this->localRotate.setX(_x);
    }

    void setRotateY(stReal _y){
        if(rotateMode == Global) this->rotate.setY(_y);
        else this->localRotate.setY(_y);
    }

    void setRotateZ(stReal _z){
        if(rotateMode == Global) this->rotate.setZ(_z);
        else this->localRotate.setZ(_z);
    }

    void setScale(Vector3<stReal>& vec){ this->scale = vec; }
    void setScaleX(stReal _x){ this->scale.setX(_x); }
    void setScaleY(stReal _y){ this->scale.setY(_y); }
    void setScaleZ(stReal _z){ this->scale.setZ(_z); }
    void setScale(stReal _value){
        setScaleX(_value);
        setScaleY(_value);
        setScaleZ(_value);
    }

    void setRotationMode(RotationMode rotMode){
        rotateMode = rotMode;
    }

    const Matrix4f getModel(){
        Matrix4f trans, rot, scaleMat, rotX, rotY, rotZ;
        trans.initTranslation(translate);
        if(rotateMode == Global){
            rot.initRotate(rotate);
        }else{
            rot.initRotate(localRotate);
        }
        scaleMat.initScale(scale);

        Matrix4f ret;
        ret = scaleMat * rot * trans;
        return ret;
    }

    std::string getInfo(){
        Matrix4f mat = getModel();
        return mat.getInfo();
    }

    template<typename T> Vector3<T> getTranslate()const{return Vector3<T>((T)translate.getX(), (T)translate.getY(), (T)translate.getZ()); }
    template<typename T> Vector3<T> getRotate()const{ return Vector3<T>( (T)rotate.getX(), (T)rotate.getY(), (T)rotate.getZ() ); }
    Euler<stReal> getLocalRotate()const{ return localRotate; }
    template<typename T> Vector3<T> getScale()const{ return Vector3<T>( (T)scale.getX(), (T)scale.getY(), (T)scale.getZ() ); }
private:
    Vector3<stReal> translate;
    Vector3<stReal> rotate;
    Euler<stReal> localRotate;
    Vector3<stReal> scale;
    RotationMode rotateMode;
};

#endif //WAHOO_TRANSFORM_H
