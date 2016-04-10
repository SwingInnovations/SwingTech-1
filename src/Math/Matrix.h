#ifndef WAHOO_MATRIX_H
#define WAHOO_MATRIX_H

#include <string>
#include <sstream>

#include "STCore.h"
#include "Vector.h"


class Matrix4f{
public:
    Matrix4f(){
        initIdentity();
    }

    void initIdentity(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(i == j){
                    m[i][j] = 1.0f;
                }else{
                    m[i][j] = 0.0f;
                }
            }
        }
    }

    void initTranslation(const Vector3<stReal>& vec){
        initTranslation(vec.getX(), vec.getY(), vec.getZ());
    }

    void initTranslation(float x, float y, float z){
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void initRotate(Vector3<stReal>& vec){
        initRotate(vec.getX(), vec.getY(), vec.getZ());
    }

    void initRotate(stReal x, stReal y, stReal z){
        Matrix4f rx, ry, rz;

        const stReal _x = toRadian(x);
        const stReal _y = toRadian(y);
        const stReal _z = toRadian(z);

        rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f;     rx.m[0][2] = 0.0f;      rx.m[0][3] = 0.0f;
        rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(_x); rx.m[1][2] = -sinf(_x); rx.m[1][3] = 0.0f;
        rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(_x); rx.m[2][2] = cosf(_x);  rx.m[2][3] = 0.0f;
        rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f;     rx.m[3][2] = 0.0f;      rx.m[3][3] = 1.0f;

        ry.m[0][0] = cosf(_y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(_y); ry.m[0][3] = 0.0f;
        ry.m[1][0] = 0.0f;     ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f;      ry.m[1][3] = 0.0f;
        ry.m[2][0] = sinf(_y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(_y);  ry.m[2][3] = 0.0f;
        ry.m[3][0] = 0.0f;     ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f;      ry.m[3][3] = 1.0f;

        rz.m[0][0] = cosf(_z); rz.m[0][1] = -sinf(_z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
        rz.m[1][0] = sinf(_z); rz.m[1][1] = cosf(_z);  rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
        rz.m[2][0] = 0.0f;     rz.m[2][1] = 0.0f;      rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
        rz.m[3][0] = 0.0f;     rz.m[3][1] = 0.0f;      rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

        Matrix4f ret;
        ret = rz * ry * rx;
        *this = ret;
    }

    void initRotation(float angle, const Vector3<stReal>& vec){
        float L = (float)(pow(vec.getX(), 2) + pow(vec.getY(), 2) + pow(vec.getZ(), 2));
        angle = toRadian(angle);

        float u = vec.getX();
        float v = vec.getY();
        float w = vec.getZ();

        float u2 = (float)pow(vec.getX(), 2);
        float v2 = (float)pow(vec.getY(), 2);
        float w2 = (float)pow(vec.getZ(), 2);

        m[0][0] = (float)(u2 + (v2 + w2) * cos((double)angle))/ L;
        m[0][1] = (float)(u * v * (1-cos((double)angle)) - w * sqrt(L) * sin((double)angle)) / L;
        m[0][2] = (float)(u * w * (1-cos((double)angle)) + v * sqrt(L) * sin((double)angle)) / L;
        m[0][3] = 0.0f;

        m[1][0] = (float)(u * v * (1 - cos((double)angle)) + w * sqrt(L) * sin((double)angle)) / L;
        m[1][1] = (float)(v2 + (u2 + w2) * cos((double)angle)) / L;
        m[1][2] = (float)(v * w * (1 - cos((double)angle)) - u * sqrt(L) * sin((double)angle)) / L;
        m[1][3] = 0.0;

        m[2][0] = (float)(u * w * (1 - cos((double)angle)) - v * sqrt(L) * sin((double)angle)) / L;
        m[2][1] = (float)(v * w * (1 - cos((double)angle)) + u * sqrt(L) * sin((double)angle)) / L;
        m[2][2] = (float)(w2 + (u2 + v2) * cos((double)angle)) / L;
        m[2][3] = 0.0;

        m[3][0] = 0.0;
        m[3][1] = 0.0;
        m[3][2] = 0.0;
        m[3][3] = 1.0;
    }

    void initScale(Vector3<stReal>& vec){
        m[0][0] = vec.getX(); m[0][1] = 0.0f;       m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f;       m[1][1] = vec.getY(); m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f;       m[2][1] = 0.0f;       m[2][2] = vec.getZ(); m[2][3] = 0.0f;
        m[3][0] = 0.0f;       m[3][1] = 0.0f;       m[3][2] = 0.0f;       m[3][3] = 1.0f;
    }

    void initScale(float x, float y, float z){
        m[0][0] = x; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = y; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = z; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void initPerpectiveProjection(float FOV, float WIDTH, float HEIGHT,
                                    float zNear, float zFar){
        const float ar = WIDTH / HEIGHT;
        const float tanHalfFOV = tanf(toRadian(FOV/2.0f));

        m[0][0] = 1.0f/(tanHalfFOV * ar); m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f;                   m[1][1] = 1.0f / tanHalfFOV;    m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f;                   m[2][1] = 0.0f; m[2][2] = -zFar/(zNear-zFar);    m[2][3] = zFar * zNear/(zNear - zFar);
        m[3][0] = 0.0f;                   m[3][1] = 0.0f; m[3][2] = 1.0f; m[3][3] = 0.0f;
    }

    void initOrthographicProjection(float width, float height, float zNear, float zFar){
        const float zRange = zFar - zNear;

        m[0][0] = 2.0f/width; m[0][1] = 0.0f;          m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f;       m[1][1] = 2.0f / height; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f;       m[2][1] = 0.0f;          m[2][2] = 2.0f/zRange;    m[2][3] = (-zFar - zNear)/zRange;
        m[3][0] = 0.0f;       m[3][1] = 0.0f;          m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void initCamera(const Vector3<stReal>& target, const Vector3<stReal>& up){
        Vector3<stReal> N = target;
        N.normalize();
        Vector3<stReal> U = up;
        U.normalize();
        U = U.cross(N);
        Vector3<stReal> V = N.cross(U);

        m[0][0] = U.getX(); m[0][1] = U.getY(); m[0][2] = U.getZ(); m[0][3] = 0.0f;
        m[1][0] = V.getX(); m[1][1] = V.getY(); m[1][2] = V.getZ(); m[1][3] = 0.0f;
        m[2][0] = N.getX(); m[2][1] = N.getY(); m[2][2] = N.getZ(); m[2][3] = 0.0f;
        m[3][0] = 0.0f;     m[3][1] = 0.0f;     m[3][2] = 0.0f;     m[3][3] = 1.0f;
    }

    void initCamera(const Vector3<stReal>& target, const Vector3<stReal>& up, Vector3<stReal> translate){
        Vector3<stReal> N = target;
        N.normalize();
        Vector3<stReal> U = up;
        U.normalize();
        U = U.cross(N);
        Vector3<stReal> V = N.cross(U);

        //translate = translate.negate();

        m[0][0] = U.getX(); m[0][1] = U.getY(); m[0][2] = U.getZ(); m[0][3] = translate.getX();
        m[1][0] = V.getX(); m[1][1] = V.getY(); m[1][2] = V.getZ(); m[1][3] = translate.getY();
        m[2][0] = N.getX(); m[2][1] = N.getY(); m[2][2] = N.getZ(); m[2][3] = translate.getZ();
        m[3][0] = 0.0f;     m[3][1] = 0.0f;     m[3][2] = 0.0f;     m[3][3] = 1.0f;
    }

    void initCamera(const Vector3<stReal>& target, const Vector3<stReal>& up, const Vector3<stReal>& view, Vector3<stReal> translate){
        Vector3<stReal> N = target;
        Vector3<stReal> U = up;
        Vector3<stReal> V = view;

        translate = translate.negate();

        m[0][0] = U.getX(); m[0][1] = U.getY(); m[0][2] = U.getZ(); m[0][3] = translate.getX();
        m[1][0] = V.getX(); m[1][1] = V.getY(); m[1][2] = V.getZ(); m[1][3] = translate.getY();
        m[2][0] = N.getX(); m[2][1] = N.getY(); m[2][2] = N.getZ(); m[2][3] = translate.getZ();
        m[3][0] = 0.0f;     m[3][1] = 0.0f;     m[3][2] = 0.0f;     m[3][3] = 1.0f;
    }

    inline Matrix4f operator*(const Matrix4f& right)const {
        Matrix4f ret;
        for (unsigned int i = 0; i < 4; i++) {
            for (unsigned int j = 0; j < 4; j++) {
                ret.m[i][j] = m[i][0] * right.m[0][j] +
                              m[i][1] * right.m[1][j] +
                              m[i][2] * right.m[2][j] +
                              m[i][3] * right.m[3][j];
            }
        }
        return ret;
    }

    Vector4<stReal> toVector4()const{
        const float _x = m[0][0] + m[0][1] + m[0][2] + m[0][3];
        const float _y = m[1][0] + m[1][1] + m[1][2] + m[1][3];
        const float _z = m[2][0] + m[2][1] + m[2][2] + m[2][3];
        const float _w = m[3][0] + m[3][1] + m[3][2] + m[3][3];
        return Vector4<stReal>(_x, _y, _z, _w);
    }

    const Matrix4f transpose()const {
        Matrix4f ret;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                ret.m[i][j] = m[j][i];
            }
        }
        return ret;
    }

    std::string getInfo(){
        std::ostringstream buff;
        for(int i = 0; i < 4; i++){
            buff << "\n[ " << m[i][0] << " , " << m[i][1] << " , " << m[i][2] << " , " << m[i][3] << "]\n";
        }
        return buff.str();
    }

    stReal m[4][4];
};

#endif //WAHOO_MATRIX_H
