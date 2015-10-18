//
// Created by NDanq on 10/14/2015.
//

#ifndef WAHOO_QUATERNION_H
#define WAHOO_QUATERNION_H

#include "STech_Core.h
#include "Vector.h"

class Vector3;

class Quaternion {
public:
    Quaternion(){
        m_val[0] = 0.0f;
        m_val[1] = 0.0f;
        m_val[2] = 0.0f;
        m_val[3] = 1.0f;
    }

    Quaternion(const float _x, const float _y, const float _z, const float _w){
        m_val[0] = _x;
        m_val[1] = _y;
        m_val[2] = _z;
        m_val[3] = _w;
    }

    void setX(const float _x){ m_val[0] = _x; }
    void setY(const float _y){ m_val[1] = _y; }
    void setZ(const float _z){ m_val[2] = _z; }
    void setW(const float _w){ m_val[3] = _w; }

    float getX()const{ return m_val[0]; }
    float getY()const{ return m_val[1]; }
    float getZ()const{ return m_val[2]; }
    float getW()const{ return m_val[3]; }

    float getLength(){ return (float)sqrt( pow(m_val[0], 2) + pow(m_val[1], 2) + pow(m_val[2], 2) + pow(m_val[3], 2)) };
    float* getData(){ return m_val; }

    Quaternion normalize(){
        float len = getLength();
        m_val[0] /= len;
        m_val[1] /= len;
        m_val[2] /= len;
        m_val[3] /= len;
        return *this;
    }

    Quaternion conjugate(){
        return Quaternion(-m_val[0], -m_val[1], -m_val[2], m_val[3]);
    }

    Vector3<float> inline toVector3f();

    inline Quaternion multiply(Quaternion& r)const{
        float _x = this->getW()*r.getX() + this->getX()*r.getW() + this->getY()* r.getZ() - this->getZ() * r.getY();
        float _y = this->getW()*r.getY() - this->getX()*r.getZ() + this->getY()*r.getW() + this->getZ()*r.getX();
        float _z = this->getW()*r.getZ() + this->getX()*r.getY() - this->getY()*r.getX() + this->getZ()*r.getW();
        float _w = this->getW()*r.getW() - this->getX()*r.getX() - this->getY()*r.getY() + this->getZ()*r.getZ();
        return Quaternion(_x, _y, _z, _w);
    }

    inline Quaternion multiply(Vector3& vec)const{
        float _x = (this->getW() * (float)vec.getX()) + (this->getY() * (float)vec.getZ()) - (this->getZ() * (float)vec.getY());
        float _y = (this->getW() * (float)vec.getY()) + (this->getZ() * (float)vec.getX()) - (this->getX() * (float)vec.getZ());
        float _z = (this->getW() * (float)vec.getZ()) + (this->getX() * (float)vec.getY()) - (this->getY() * (float)vec.getX());
        float _w = -(this->getX() * (float)vec.getX()) - (this->getY() * (float)vec.getY()) - (this->getZ() * (float)vec.getZ()));
        return Quaternion(_x, _y, _z, _w);
    }

private:
    float m_val[4];
};

Vector3<float> inline Quaternion::toVector3f() {
    Vector3<float> ret(m_val[0], m_val[1], m_val[2]);
    return ret;
}


#endif //WAHOO_QUATERNION_H
