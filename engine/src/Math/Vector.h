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
    /**
     * Constructs a new Vector2
     * @return
     */
    Vector2(){
        m_val[0] = 0;
        m_val[1] = 0;
    }

    /**
     * Constructs a new Vector 2
     * @param _x X Component
     * @param _y Y Component
     * @return
     */
    Vector2(T _x, T _y){
        m_val[0] = _x;
        m_val[1] = _y;
    }

    /**
     * Linearly interpolates between two vectors.
     * @param start Start Vector
     * @param end   Destination Vector
     * @param step  Progression between two vectors(0.0-1.0)
     * @return
     */
    static Vector2 Lerp(const Vector2& start, const Vector2& end, const stReal& step){
        stReal st1 = 1.0f - step;
        T x = (st1 * start.getX()) + (step * end.getX());
        T y = (st1 * start.getY()) + (step * end.getY());
        return Vector2(x, y);
    }

    /**
     * Sets the X Component
     * @param _x
     */
    void setX(T _x){
        m_val[0] = _x;
    }

    /**
     * Sets the Y Component
     * @param _y
     */
    void setY(T _y){
        m_val[1] = _y;
    }

    /**
     * Sets the X and Y Components
     * @param _x X Component
     * @param _y Y Component
     */
    void set(T _x, T _y){
        m_val[0] = _x;
        m_val[1] = _y;
    }

    /**
     * Returns the X Component of Vector2
     * @return X Component
     */
    T getX() const{ return m_val[0]; }

    /**
     * Returns the Y Component
     * @return Y Component
     */
    T getY() const{ return m_val[1]; }

    /**
     * Returns the data of the Vector as an array of type T.
     * @return data
     */
    T* getData(){ return m_val; }

    /**
     * Returns the magnitude of the vector.
     * @return Magnitude.
     */
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

    static Vector3 Lerp(const Vector3& start, const Vector3& end, const stReal& step){
        stReal st1 = 1.0f - step;
        const T x = (st1 * start.getX()) + (step * end.getX());
        const T y = (st1 * start.getY()) + (step * end.getY());
        const T z = (st1 * start.getZ()) + (step * end.getZ());
        return Vector3(x, y, z);
    }

    inline void setX(const T& _x){ m_Val[0] = _x; }
    inline void setY(const T& _y){ m_Val[1] = _y; }
    inline void setZ(const T& _z){ m_Val[2] = _z; }

    inline T getX() const{ return m_Val[0]; }
    inline T getY() const{ return m_Val[1]; }
    inline T getZ() const{ return m_Val[2]; }

    inline T* getData(){ return m_Val; }

    inline double getLength(){
        double _x = (double)getX();
        double _y = (double)getY();
        double _z = (double)getZ();
        return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
    }

    inline Vector3 normalize(){
        auto len = getLength();
        if(len > 0){
            m_Val[0] /= getLength();
            m_Val[1] /= getLength();
            m_Val[2] /= getLength();
        }
        return *this;
    }

    inline Vector3 negate(){
        m_Val[0] = -abs(m_Val[0]);
        m_Val[1] = -abs(m_Val[1]);
        m_Val[2] = -abs(m_Val[2]);
        return *this;
    }

    inline std::string getInfo() const {
        std::ostringstream str;
        str << "[ X: " << m_Val[0] << " Y: " << m_Val[1] << " Z: " << m_Val[2] <<" ] " << std::endl;
        return str.str();
    }

    inline void rotate(stReal angle, Vector3& axis){
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

    inline double dot(const Vector3& other){
        return sqrt(this->getX() * other.getX() + this->getY() * other.getY() + other.getZ() * other.getZ());
    }

    inline Vector3 cross(const Vector3& other)const{
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
        return Vector3(x, y, z);
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

    template<typename U>
    Vector4(Vector3<U> vec, T _W){
        m_Val[0] = (T)vec.getX();
        m_Val[1] = (T)vec.getY();
        m_Val[2] = (T)vec.getZ();
        m_Val[3] = _W;
    }

    inline void setX(T _x){ m_Val[0] = _x; }
    inline void setY(T _y){ m_Val[1] = _y; }
    inline void setZ(T _z){ m_Val[2] = _z; }
    inline void setW(T _w){ m_Val[3] = _w; }

    inline T getX()const{ return m_Val[0]; }
    inline T getY()const{ return m_Val[1]; }
    inline T getZ()const{ return m_Val[2]; }
    inline T getW()const{ return m_Val[3]; }

    inline double getLength()const{
        double x = (double)getX();
        double y = (double)getY();
        double z = (double)getZ();
        double w = (double)getW();

        return sqrt( x * x + y * y + z * z + w * w);
    }

    inline Vector4 normalize()const{
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

    Vector3<T> toVector3Norm()const{
        T x = this->getX() / this->getW();
        T y = this->getY() / this->getW();
        T z = this->getZ() / this->getW();
        return Vector3<T>(x, y, z);
    }

private:
    T m_Val[4];
};




#endif //WAHOO_VECTOR_H
