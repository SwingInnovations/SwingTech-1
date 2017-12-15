#ifndef WAHOO_QUATERNION_H
#define WAHOO_QUATERNION_H


#include <assimp/quaternion.h>
#include "../../include/json11/json11.hpp"
#include "STCore.h"

template <typename T> class Vector3;

using namespace json11;

class Quaternion {
public:
    /** Default constructor
     *
     * @return
     */
    Quaternion(){
        m_val[0] = 0.0f;
        m_val[1] = 0.0f;
        m_val[2] = 0.0f;
        m_val[3] = 1.0f;
    }

    /** Quaternion Constructor
     *
     * @param _x    X - Component
     * @param _y    Y - Component
     * @param _z    Z - Component
     * @param _w    W - Component
     * @return
     */
    Quaternion(const float _x, const float _y, const float _z, const float _w){
        m_val[0] = _x;
        m_val[1] = _y;
        m_val[2] = _z;
        m_val[3] = _w;
    }

    /**
     * Initializes ST Quaternion from assimp quaternion
     * @param quaternion
     * @return
     */
    static Quaternion From(aiQuaternion quaternion){
        return Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
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

    /**Normalizes the quaternion.
     *
     * @return quaternion normalized.
     */
    inline Quaternion normalize(){
        float len = getLength();
        m_val[0] /= len;
        m_val[1] /= len;
        m_val[2] /= len;
        m_val[3] /= len;
        return *this;
    }

    /**Returns the Conjugate of the Quaternion
     *
     * @return Conjugate of the quaternion.
     */
    inline Quaternion conjugate(){
        return Quaternion(-m_val[0], -m_val[1], -m_val[2], m_val[3]);
    }

    /**Converts Quaternion to Vector3
     *
     * @return Vector3-ized quaternion.
     */
    template<typename T>inline Vector3<T> toVector3(){
        T _x = (T)m_val[0];
        T _y = (T)m_val[1];
        T _z = (T)m_val[2];

        Vector3<T> ret(_x, _y, _z);
        return ret;
    }
    static stReal dot(Quaternion& q1, Quaternion& q2);

    static Quaternion lerp(Quaternion& q1, Quaternion& q2, stReal t);

    static Quaternion slerp(Quaternion& q1, Quaternion& q2, stReal t);

    Quaternion multiply(Quaternion& r)const;

    Quaternion multiply(Vector3<stReal>& vec)const;

    const Quaternion operator*(float scale)const;

    const Quaternion operator+(const Quaternion& q)const;

    const Quaternion operator/(float scale) const;

    const Quaternion operator -()const;

    Json to_json()const;

private:
    float m_val[4];
};

#endif //WAHOO_QUATERNION_H
