#include "Vector.h"

Vector3f::Vector3f() {
    m_Val[0] = 0;
    m_Val[1] = 0;
    m_Val[2] = 0;
}

Vector3f::Vector3f(stReal _x, stReal _y, stReal _z) {
    m_Val[0] = _x;
    m_Val[1] = _y;
    m_Val[2] = _z;
}

Vector3f::Vector3f(Vector2f in, stReal _z) {
    m_Val[0] = in.getX();
    m_Val[1] = in.getY();
    m_Val[2] = 0.0;
}

Vector3f Vector3f::Min(const Vector3f &v1, const Vector3f &v2) {
    const stReal x = v1.getX() < v2.getX() ? v1.getX() : v2.getX();
    const stReal y = v1.getY() < v2.getY() ? v1.getY() : v2.getY();
    const stReal z = v1.getZ() < v2.getZ() ? v1.getZ() : v2.getZ();
    return Vector3f(x, y, z);
}

Vector3f Vector3f::Lerp(const Vector3f &start, const Vector3f &end, const stReal &step) {
    stReal st1 = 1.0f - step;
    const stReal x = (st1 * start.getX()) + (step * end.getX());
    const stReal y = (st1 * start.getY()) + (step * end.getY());
    const stReal z = (st1 * start.getZ()) + (step * end.getZ());
    return Vector3f(x, y, z);
}

void Vector3f::rotate(stReal angle, Vector3f &axis) {
    float hSinF = sinf(toRadian(angle/2));
    float hCosF = cosf(toRadian(angle/2));

    const float rX = (float)axis.getX() * hSinF;
    const float rY = (float)axis.getY() * hSinF;
    const float rZ = (float)axis.getZ() * hSinF;
    const float rW = hCosF;

    Quaternion rotateQ(rX ,rY, rZ, rW);
    Quaternion ConjQ, W;
    ConjQ = rotateQ.conjugate();
    //W = rotateQ.multiply(*this).multiply(ConjQ);

    this->m_Val[0] = W.getX();
    this->m_Val[1] = W.getY();
    this->m_Val[2] = W.getZ();
}

std::string Vector3f::getInfo() const {
    std::ostringstream str;
    str << "[ X: " << m_Val[0] << " Y: " << m_Val[1] << " Z: " << m_Val[2] <<" ] " << std::endl;
    return str.str();
}
