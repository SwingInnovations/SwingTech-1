#include "Quaternion.h"
#include "STCore.h"
#include "Vector.h"

float Quaternion::dot(Quaternion &q1, Quaternion &q2) {
    auto vec1 = q1.toVector3<stReal>();
    auto vec2 = q2.toVector3<stReal>();
    auto s1 = q1.getW();
    auto s2 = q2.getW();
    return ((stReal)vec1.dot(vec2) + s1 * s2);
}

Quaternion Quaternion::multiply(Vector3D &vec) const {
    float _x = (this->getW()*(float)vec.getX()) + (this->getY() * (float)vec.getZ()) - (this->getZ() * (float)vec.getY());
    float _y = (this->getW()*(float)vec.getY()) + (this->getZ() * (float)vec.getX()) - (this->getX() * (float)vec.getZ());
    float _z = (this->getW()*(float)vec.getZ()) + (this->getX() * (float)vec.getY()) - (this->getY() * (float)vec.getX());
    float _w = -(this->getX()*(float)vec.getX()) - (this->getY() * (float)vec.getY()) - (this->getZ() * (float)vec.getZ());
    return Quaternion(_x, _y, _z, _w);
}

Quaternion Quaternion::slerp(Quaternion &q1, Quaternion &q2, stReal t) {
    Quaternion q3;
    auto dot = Quaternion::dot(q1, q2);
    if(dot < 0){
        dot = -dot;
        q3 = -q2;
    }else q3 = q2;

    if(dot < 0.95f){
        float angle = acosf(dot);
        return (q1 * sinf(angle * (1-t)) + q3 * sinf(angle*t)) / sinf(angle);
    }return lerp(q1, q3, t);
}

Quaternion Quaternion::lerp(Quaternion &q1, Quaternion &q2, stReal t) {
    auto ret = (q1 * (1-t) + q2 * t);
    return ret.normalize();
}
