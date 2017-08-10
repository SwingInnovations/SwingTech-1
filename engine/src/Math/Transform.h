#ifndef WAHOO_TRANSFORM_H
#define WAHOO_TRANSFORM_H

#include <iostream>

#include "STCore.h"
#include "Matrix.h"
#include "Vector.h"
#include "Euler.h"

class STEntity;

class Transform{
public:
    enum RotationMode: unsigned char {Global = 0, Local = 1};

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
    inline void setTranslate(stReal _value){
        setTranslateX(_value);
        setTranslateY(_value);
        setTranslateZ(_value);
    }

    inline void setRotate(Vector3<stReal>& vec){
        this->rotate = vec;
    }

    inline void setRotateX(stReal _x){
        rotate.setX(_x);

    }

    inline void setRotateY(stReal _y){
        rotate.setY(_y);
    }

    inline void setRotateZ(stReal _z){
        rotate.setZ(_z);
    }

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

    const Matrix4f getModel(){
        Matrix4f trans, rot, scaleMat, rotX, rotY, rotZ;
        trans.initTranslation(translate);
        if(rotateMode == Global){
            rot.initRotate(rotate);
        }else{
            Matrix4f negTransMat;
            negTransMat.initTranslation(-translate.getX(), -translate.getY(), -translate.getZ());
            rot.initRotate(rotate);
            rot = trans * rot * negTransMat;
        }
        scaleMat.initScale(scale);

        Matrix4f ret;
        ret = scaleMat * rot * trans;
        return ret;
    }

    inline std::string getInfo(){
        Matrix4f mat = getModel();
        return mat.getInfo();
    }

    Vector3<stReal> getTranslate()const{return translate; }
    template<typename T> Vector3<T> getRotate()const{ return Vector3<T>( (T)rotate.getX(), (T)rotate.getY(), (T)rotate.getZ() ); }
    template<typename T> Vector3<T> getScale()const{ return Vector3<T>( (T)scale.getX(), (T)scale.getY(), (T)scale.getZ() ); }
    Vector3<stReal> getTranslateF()const{ return translate; }
    Vector3<stReal> getRotateF() const {return rotate;}
    Vector3<stReal> getScaleF() const {return scale;}
private:
    STEntity* parent;
    Vector3<stReal> translate;
    Vector3<stReal> rotate;
    Vector3<stReal> scale;
    RotationMode rotateMode;
};


#endif //WAHOO_TRANSFORM_H
