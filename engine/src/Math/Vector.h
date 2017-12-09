#ifndef WAHOO_VECTOR_H
#define WAHOO_VECTOR_H

#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

#include "STCore.h"
#include "Quaternion.h"

#include "../../include/json11/json11.hpp"
#include "../../include/assimp/vector3.h"

using namespace json11;

class Quaternion;

template<typename T>
class Vector2{
public:
    static Vector2 FromJson(const std::string& jsonFile);

    static Vector2 FromJson(const Json& jsonDoc);

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

    /**
     * Normalizes Vector
     * @return vector normalized.
     */
    Vector2 normalize(){
        m_val[0] /= getLength();
        m_val[1] /= getLength();
        return *this;
    }

    /**
     * Calculates the dot product
     * @param other
     * @return Dot product of two vectors.
     */
    inline double dot(Vector2& other){
        double x = this->getX();
        double y = this->getY();
        double _x = other.getX();
        double _y = other.getY();

        return x * _x + y * _y;
    }

    /**
     * Printed components of the Vector
     * @return
     */
    std::string info()const{
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

    Json to_json()const{
        return Json::object{
                {"x", m_val[0]},
                {"y", m_val[1]}
        };
    }

private:
    T m_val[2];
};
template<typename T>
Vector2<T> Vector2<T>::FromJson(const std::string &jsonFile) {
    std::ifstream in(jsonFile);
    std::stringstream readBuff;
    readBuff << in.rdbuf();
    std::string errStr;
    auto doc = Json::parse(readBuff.str(), errStr, JsonParse::STANDARD);
    auto vX = (T)doc["x"].number_value();
    auto vY = (T)doc["y"].number_value();
    return Vector2<stReal>(vX, vY);
}

template<typename T>
Vector2<T> Vector2<T>::FromJson(const Json& jsonDoc) {
    auto vX = jsonDoc["x"];
    auto vY = jsonDoc["y"];
    auto ret = Vector2<T>((T)vX.number_value(), (T)vY.number_value());
    return ret;
}

template<typename T>
class Vector3 {
public:

    static Vector3 FromJson(const std::string& str);
    static Vector3 FromJson(const Json& jsonDoc);

    /**
     * Default Vector3 Constructor
     * @return
     */
    Vector3(){
        m_Val[0] = 0;
        m_Val[1] = 0;
        m_Val[2] = 0;
    }

    /** Vector3 Constructor
     *
     * @param _x - X Component
     * @param _y - Y Component
     * @param _z - Z Component
     * @return Vector3()
     */
    Vector3(T _x, T _y, T _z){
        m_Val[0] = _x;
        m_Val[1] = _y;
        m_Val[2] = _z;
    }

    /**Vector3 Constructor that expands a Vector2
     *
     * @param in Vector 2 that will occupy the X and Y Components
     * @param _z - Z Component
     * @return
     */
    Vector3(Vector2<T> in, T _z){
        m_Val[0] = in.getX();
        m_Val[1] = in.getY();
        m_Val[2] = 0.0;
    }

    static Vector3<stReal> From(const aiVector3D& vec){
        return Vector3<stReal>(vec.x, vec.y, vec.z);
    }

    /**
     * Constructs an minimum vector on a component basis
     * @param v1
     * @param v2
     * @return
     */
    static Vector3 Min(const Vector3& v1, const Vector3& v2){
        const T x = v1.getX() < v2.getX() ? v1.getX() : v2.getX();
        const T y = v1.getY() < v2.getY() ? v1.getY() : v2.getY();
        const T z = v1.getZ() < v2.getZ() ? v1.getZ() : v2.getZ();
        return Vector3(x, y, z);
    }

    static Vector3 Max(const Vector3& v1, const Vector3& v2){
        const T x = v1.getX() > v2.getX() ? v1.getX() : v2.getX();
        const T y = v1.getY() > v2.getY() ? v1.getY() : v2.getY();
        const T z = v1.getZ() > v2.getZ() ? v1.getZ() : v2.getZ();
        return Vector3(x, y, z);
    }

    /**Linearly interpolates between two vectors.
     *
     * @param start     Start Vector
     * @param end       Destination Vector
     * @param step      Progression between two vectors(0.0-1.0)
     * @return  Interpolated Vector based on progression.
     */
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

    /**
     * Returns the length of the Vector.
     * @return
     */
    inline double getLength()const{
        double _x = (double)getX();
        double _y = (double)getY();
        double _z = (double)getZ();
        return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
    }

    /**
     *  Normalizes the Vector.
     * @return Normalized Vector
     */
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

    /**
     * Printed components of the Vector
     * @return Componenets in stirng form.
     */
    inline std::string getInfo() const {
        std::ostringstream str;
        str << "[ X: " << m_Val[0] << " Y: " << m_Val[1] << " Z: " << m_Val[2] <<" ] " << std::endl;
        return str.str();
    }

    /**Rotates the Vector by an angle and Axis
     *
     * @param angle Amount to rotate(degrees)
     * @param axis  Vector3 Axis
     */
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

    /**Calculate the Dot Product between two vectors
     *
     * @param other
     * @return Dot Product.
     */
    inline double dot(const Vector3& other){
        return this->getX() * other.getX() + this->getY() * other.getY() + this->getZ() * other.getZ();
    }

    /**Calculates the Cross Product between two vectors.
     *
     * @param other Other Vector
     * @return Vector3 that is perpendicular to the two inputted vectors.
     */
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
        return Vector3(x, y, z);
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

    Vector3 operator*= (const T& other){
        m_Val[0] *= other;
        m_Val[1] *= other;
        m_Val[2] *= other;
        return *this;
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

    const bool operator<= (const Vector3& other)const{
        return ((getX() <= other.getX()) && (getY() <= other.getY()) && (getZ() <= other.getZ()));
    }

    const bool operator>= (const Vector3& other)const{
        return ((getX() >= other.getX()) && (getY() >= other.getY()) && (getZ() >= other.getZ()) );
    }

    const bool operator== (const Vector3& other)const{
        return (getX() == other.getX()) && (getY() == other.getY()) && (getZ()==other.getZ());
    }

    Json to_json()const{
        return Json::object{
                {"x", m_Val[0]},
                {"y", m_Val[1]},
                {"z", m_Val[2]}
        };
    }

private:
    T m_Val[3];
};

template<typename  T>
Vector3<T> Vector3<T>::FromJson(const std::string &str) {
    std::ifstream in(str);
    std::stringstream readBuff;
    readBuff << in.rdbuf();
    std::string err;
    auto doc = Json::parse(readBuff.str(), err, JsonParse::STANDARD);
    auto vX = (T)doc["x"].number_value();
    auto vY = (T)doc["y"].number_value();
    auto vZ = (T)doc["z"].number_value();
    return Vector3<T>( vX, vY, vZ);
}

template<typename T>
Vector3<T> Vector3<T>::FromJson(const Json &jsonDoc) {
    auto vX = jsonDoc["x"].number_value();
    auto vY = jsonDoc["y"].number_value();
    auto vZ = jsonDoc["z"].number_value();
    return Vector3<T>((T)vX, (T)vY, (T)vZ);
}

template<typename T>
class Vector4{
public:
    static Vector4 FromJson(const std::string& jsonDoc);
    static Vector4 FromJson(const Json& doc);

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
        return getX() * other.getX() + getY() * other.getY() + getZ() * other.getZ() + getW() * other.getW();
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

    Vector3<T> toVector3() const {
        T x = this->getX();
        T y = this->getY();
        T z = this->getZ();
        return Vector3<T>(x, y, z);
    }

    Vector3<T> toVector3Norm() const {
        T x = this->getX() / this->getW();
        T y = this->getY() / this->getW();
        T z = this->getZ() / this->getW();
        return Vector3<T>(x, y, z);
    }

    Json to_json()const{
        return Json::object{
                {"x", m_Val[0]},
                {"y", m_Val[1]},
                {"z", m_Val[2]},
                {"w", m_Val[3]}
        };
    }

private:
    T m_Val[4];
};

template<typename T>
Vector4<T> Vector4<T>::FromJson(const std::string &jsonDoc) {
    std::ifstream in(jsonDoc);
    std::stringstream readBuff;
    readBuff << in.rdbuf();
    in.close();

    std::string errStr;
    auto doc = Json::parse(readBuff.str(), errStr, JsonParse::STANDARD);
    auto vX = (T)doc["x"].number_value();
    auto vY = (T)doc["y"].number_value();
    auto vZ = (T)doc["z"].number_value();
    auto vW = (T)doc["w"].number_value();

    return Vector4<T>(vX, vY, vZ, vW);
}

template<typename T>
Vector4<T> Vector4<T>::FromJson(const Json &doc) {
    auto vX = (T)doc["x"].number_value();
    auto vY = (T)doc["y"].number_value();
    auto vZ = (T)doc["z"].number_value();
    auto vW = (T)doc["w"].number_value();
    return Vector4<T>(vX, vY, vZ, vW);
}

typedef  Vector2<stReal> Vector2D;
typedef  Vector3<stReal> Vector3D;
typedef  Vector4<stReal> Vector4D;


#endif //WAHOO_VECTOR_H


