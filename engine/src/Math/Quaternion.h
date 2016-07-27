#ifndef WAHOO_QUATERNION_H
#define WAHOO_QUATERNION_H

template<typename>class Vector3;

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

    inline void setX(const float _x){ m_val[0] = _x; }
    inline void setY(const float _y){ m_val[1] = _y; }
    inline void setZ(const float _z){ m_val[2] = _z; }
    inline void setW(const float _w){ m_val[3] = _w; }

    inline float getX()const{ return m_val[0]; }
    inline float getY()const{ return m_val[1]; }
    inline float getZ()const{ return m_val[2]; }
    inline float getW()const{ return m_val[3]; }

    inline float getLength(){ return (float)sqrt( pow(m_val[0], 2) + pow(m_val[1], 2) + pow(m_val[2], 2) + pow(m_val[3], 2)); }
    inline float* getData(){ return m_val; }

    inline Quaternion normalize(){
        float len = getLength();
        m_val[0] /= len;
        m_val[1] /= len;
        m_val[2] /= len;
        m_val[3] /= len;
        return *this;
    }

    inline Quaternion conjugate(){
        return Quaternion(-m_val[0], -m_val[1], -m_val[2], m_val[3]);
    }

    template<typename T>inline Vector3<T> toVector3(){
        T _x = (T)m_val[0];
        T _y = (T)m_val[1];
        T _z = (T)m_val[2];

        Vector3<T> ret(_x, _y, _z);
        return ret;
    }

    inline Quaternion multiply(Quaternion& r)const{
        float _x = this->getW()*r.getX() + this->getX()*r.getW() + this->getY()*r.getZ() - this->getZ() * r.getY();
        float _y = this->getW()*r.getY() - this->getX()*r.getZ() + this->getY()*r.getW() + this->getZ()*r.getX();
        float _z = this->getW()*r.getZ() + this->getX()*r.getY() - this->getY()*r.getX() + this->getZ()*r.getW();
        float _w = this->getW()*r.getW() - this->getX()*r.getX() - this->getY()*r.getY() - this->getZ()*r.getZ();
        return Quaternion(_x, _y, _z, _w);
    }

    template<typename T>inline Quaternion multiply(Vector3<T>& vec)const{
        float _x = (this->getW()*(float)vec.getX()) + (this->getY() * (float)vec.getZ()) - (this->getZ() * (float)vec.getY());
        float _y = (this->getW()*(float)vec.getY()) + (this->getZ() * (float)vec.getX()) - (this->getX() * (float)vec.getZ());
        float _z = (this->getW()*(float)vec.getZ()) + (this->getX() * (float)vec.getY()) - (this->getY() * (float)vec.getX());
        float _w = -(this->getX()*(float)vec.getX()) - (this->getY() * (float)vec.getY()) - (this->getZ() * (float)vec.getZ());
        return Quaternion(_x, _y, _z, _w);
    }

private:
    float m_val[4];
};

#endif //WAHOO_QUATERNION_H
