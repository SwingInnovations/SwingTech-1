#ifndef WAHOO_VECTOR_H
#define WAHOO_VECTOR_H

#include <cmath>
#include <string>
#include <sstream>

#include "STCore.h"
#include "Quaternion.h"

class Quaternion;

template<typename T>
class Vector2{
public:
    Vector2(){
        m_val[0] = 0;
        m_val[1] = 0;
    }

    Vector2(T _x, T _y){
        m_val[0] = _x;
        m_val[1] = _y;
    }

    void setX(T _x){
        m_val[0] = _x;
    }

    void setY(T _y){
        m_val[1] = _y;
    }

    T getX() const{ return m_val[0]; }
    T getY() const{ return m_val[1]; }

    T* getData(){ return m_val; }

    inline double getLength() const{
        double _x = m_val[0];
        double _y = m_val[1];
        return sqrt(_x * _x + _y * _y);
    }

    Vector2 normalize(){
        m_val[0] /= getLength();
        m_val[1] /= getLength();
        return *this;
    }

    inline double dot(Vector2& other){
        double x = this->getX();
        double y = this->getY();
        double _x = other.getX();
        double _y = other.getY();

        return sqrt( x * _x + _y * y);
    }

    std::string info(){
        return "X: " << getX() << "Y: " << getY() << "/n";
    }

    const Vector2 operator+ (const T other){
        T _x = getX() + other;
        T _y = getY() + other;
        return Vector2(_x, _y);
    }

    const Vector2 operator+(const Vector2& other){
        T _x = getX() + other.getX();
        T _y = getY() + other.getY();
        return Vector2(_x, _y);
    }

    const Vector2 operator- (const T other){
        T _x = getX() - other;
        T _y = getY() - other;
        return Vector2(_x, _y);
    }

    const Vector2 operator- (const Vector2& other){
        T _x = getX() - other.getX();
        T _y = getY() - other.getY();
        return Vector2(_x, _y);
    }

    const Vector2 operator* (const T other){
        T _x = getX() * other;
        T _y = getY() * other;
        return Vector2(_x, _y);
    }

    const Vector2 operator* (const Vector2& other){
        T _x = getX() * other.getX();
        T _y = getY() * other.getY();
        return Vector2(_x, _y);
    }

    const Vector2 operator/ (const T other){
        T _x = getX() / other;
        T _y = getY() / other;
        return Vector2(_x, _y);
    }

    const Vector2 operator/ (const Vector2& other){
        T _x = getX() / other.getX();
        T _y = getY() / other.getY();
        return Vector2(_x, _y);
    }


private:
    T m_val[2];
};

template<typename T>
class Vector3 {
public:
    Vector3(){
        m_Val[0] = 0;
        m_Val[1] = 0;
        m_Val[2] = 0;
    }

    Vector3(T _x, T _y, T _z){
        m_Val[0] = _x;
        m_Val[1] = _y;
        m_Val[2] = _z;
    }

    Vector3(Vector2<T> in, T _z){
        m_Val[0] = in.getX();
        m_Val[1] = in.getY();
        m_Val[2] = 0.0;
    }

    void setX(const T& _x){ m_Val[0] = _x; }
    void setY(const T& _y){ m_Val[1] = _y; }
    void setZ(const T& _z){ m_Val[2] = _z; }

    T getX() const{ return m_Val[0]; }
    T getY() const{ return m_Val[1]; }
    T getZ() const{ return m_Val[2]; }

    T* getData(){ return m_Val; }

    double getLength(){
        double _x = (double)getX();
        double _y = (double)getY();
        double _z = (double)getZ();
        return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
    }

    Vector3 normalize(){
        m_Val[0] /= getLength();
        m_Val[1] /= getLength();
        m_Val[2] /= getLength();
        return *this;
    }

    Vector3 negate(){
        m_Val[0] = -abs(m_Val[0]);
        m_Val[1] = -abs(m_Val[1]);
        m_Val[2] = -abs(m_Val[2]);
        return *this;
    }

    std::string getInfo() const {
        std::ostringstream str;
        str << "[ X: " << m_Val[0] << " Y: " << m_Val[1] << " Z: " << m_Val[2] <<" ] " << std::endl;
        return str.str();
    }

    void rotate(stReal angle, Vector3& axis){
        float hSinF = sinf(toRadian(angle/2));
        float hCosF = cosf(toRadian(angle/2));

        const float rX = (float)axis.getX() * hSinF;
        const float rY = (float)axis.getY() * hSinF;
        const float rZ = (float)axis.getZ() * hSinF;
        const float rW = hCosF;

        Quaternion rotateQ(rX ,rY, rZ, rW);
        Quaternion ConjQ, W;
        ConjQ = rotateQ.conjugate();
        W = rotateQ.multiply(*this).multiply(ConjQ);

        this->m_Val[0] = W.getX();
        this->m_Val[1] = W.getY();
        this->m_Val[2] = W.getZ();
    }

    double dot(const Vector3& other){
        return sqrt(this->getX() * other.getX() + this->getY() * other.getY() + other.getZ() * other.getZ());
    }

    Vector3 cross(const Vector3& other)const{
        T _x = (this->getY() * other.getZ()) - (this->getZ() * other.getY());
        T _y = (this->getZ() * other.getX()) - (this->getX() * other.getZ());
        T _z = (this->getX() * other.getY()) - (this->getY() * other.getX());
        Vector3 ret(_x, _y, _z);
        return ret;
    }

    const Vector3 operator+ (const T& other)const{
        T x = getX() + other;
        T y = getY() + other;
        T z = getZ() + other;
        return Vector3(x, y, z);
    }

    const Vector3 operator+ (const Vector3& other)const{
        T x = getX() + other.getX();
        T y = getY() + other.getY();
        T z = getZ() + other.getZ();
    }

    const Vector3 operator- (const T other)const{
        T x = getX() - other;
        T y = getY() - other;
        T z = getZ() - other;
        return Vector3(x, y, z);
    }

    const Vector3 operator- (const Vector3& other)const{
        T x = getX() - other.getX();
        T y = getY() - other.getY();
        T z = getZ() - other.getZ();
        return Vector3(x, y, z);
    }

    const Vector3 operator* (const T& other)const{
        T x = getX() * other;
        T y = getY() * other;
        T z = getZ() * other;
        return Vector3(x, y, z);
    }

    const Vector3 operator* (const Vector3& other)const{
        T x = getX() * other.getX();
        T y = getY() * other.getY();
        T z = getZ() * other.getZ();
        return Vector3(x, y, z);
    }

    const Vector3 operator/ (const T& other)const{
        T x = getX() / other;
        T y = getY() / other;
        T z = getZ() / other;
        return Vector3(x, y, z);
    }

    const Vector3 operator/ (const Vector3& other)const{
        T x = getX() / other.getX();
        T y = getY() / other.getY();
        T z = getZ() / other.getZ();
    }

private:
    T m_Val[3];
};

template<typename T>
class Vector4{
public:
    Vector4(){
        for(int i = 0; i < 4; i++){
            m_Val[i] = 0;
        }
    }
    Vector4(T _x, T _y, T _z, T _w){
        m_Val[0] = _x;
        m_Val[1] = _y;
        m_Val[2] = _z;
        m_Val[3] = _w;
    }

    void setX(T _x){ m_Val[0] = _x; }
    void setY(T _y){ m_Val[1] = _y; }
    void setZ(T _z){ m_Val[2] = _z; }
    void setW(T _w){ m_Val[3] = _w; }

    T getX()const{ return m_Val[0]; }
    T getY()const{ return m_Val[1]; }
    T getZ()const{ return m_Val[2]; }
    T getW()const{ return m_Val[3]; }

    double getLength(){
        double x = (double)getX();
        double y = (double)getY();
        double z = (double)getZ();
        double w = (double)getW();

        return sqrt( x * x + y * y + z * z + w * w);
    }

    Vector4 normalize(){
        double len = getLength();
        m_Val[0] /= len;
        m_Val[1] /= len;
        m_Val[2] /= len;
        m_Val[3] /= len;
        return *this;
    }

    inline double dot(const Vector4& other){
        return sqrt(getX() * other.getX() + getY() * other.getY() +
                    getZ * other.getZ() + getW() * other.getW());
    }

    const Vector4 operator+(const Vector4& other){
        T x = getX() + other.getX();
        T y = getY() + other.getY();
        T z = getZ() + other.getZ();
        T w = getW() + other.getW();
        return Vector4(x, y, z, w);
    }

    const Vector4 operator*(const Vector4& other){
        T x = getX() * other.getX();
        T y = getY() * other.getY();
        T z = getZ() * other.getZ();
        T w = getW() * other.getW();
        return Vector4(x, y, z, w);
    }

    Vector3<T> toVector3()const{
        T x = this->getX();
        T y = this->getY();
        T z = this->getZ();
        return Vector3<T>(x, y, z);
    }


private:
    T m_Val[4];
};




#endif //WAHOO_VECTOR_H
