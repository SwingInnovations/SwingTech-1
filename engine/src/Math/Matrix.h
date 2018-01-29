#ifndef WAHOO_MATRIX_H
#define WAHOO_MATRIX_H

#include <string>
#include <sstream>
#include <assimp/matrix4x4.h>

#include "STCore.h"
#include "Vector.h"
#include "Euler.h"

class Matrix4f{
public:
    Matrix4f();
    /**
     * Initializes a LookAt Matrix
     * @param eye       Position
     * @param center    Target
     * @param up        Up Vector
     * @return
     */
    static Matrix4f LookAt(const Vector3D eye, const Vector3D center, const Vector3D up);

    /**
     * Initializes a LookAt Matrix
     * @param position
     * @param direction
     * @param up
     * @return
     */
    static Matrix4f LookAt(const Vector3D position, const Vector4D direction, const Vector3D up);

    /**
     * Wrapper Function. Creates ST Matrix 4x4 from assimp Matrix
     * @param matrix4x4         assimp matrix
     * @return                  Matrix4f
     */
    static Matrix4f From(const aiMatrix4x4& matrix4x4);

    /**
     * Initializes an Matrix4x4 with Identity Matrix
     */
    void initIdentity();

    /**
     * Initializes a Translation Matrix from Vector
     * @param vec
     * @return
     */
    Matrix4f initTranslation(const Vector3D& vec);

    /**
     * Initializes a Translation Matrix from real values.
     * @param x
     * @param y
     * @param z
     * @return
     */
    Matrix4f initTranslation(float x, float y, float z);

    /**
     * Initializes a Rotation Matrix from a Vector
     * @param vec
     * @return
     */
    Matrix4f initRotate(const Vector3D& vec){
        *this = initRotate(vec.getX(), vec.getY(), vec.getZ());
        return *this;
    }

    /**
     * Initalizes a Rotation Matrix from real values;
     * @param x
     * @param y
     * @param z
     * @return
     */
    Matrix4f initRotate(stReal x, stReal y, stReal z);

    /**
     * Initializes a Quaternion based Rotation Matrix.
     * @param euler
     */
    Matrix4f initRotate(const Euler3D &euler);

    /**
     * Initializes a Rotation Matrix from a Quaternion.
     * @param q
     * @return
     */
    Matrix4f initRotation(Quaternion& q);

    /**
     * Initalizes a Rotation Matrix based off an angle vector and real angle value.
     * @param vec
     * @param angle
     */
    void initRotation(const Vector3D& vec, const stReal angle);

    /**
     * Initalizes a Rotation Matrix
     * @param angle
     * @param vec
     */
    void initRotation(float angle, const Vector3D& vec);

    /**
     * Initializes a Scale Matrix from Vector
     * @param vec
     * @return
     */
    Matrix4f initScale(const Vector3D& vec);

    /**
     * Initializes a Scale Matrix based off real values.
     * @param x
     * @param y
     * @param z
     * @return
     */
    Matrix4f initScale(float x, float y, float z);

    /**
     * Initializes Perspective Projection Matrix
     * @param FOV
     * @param WIDTH
     * @param HEIGHT
     * @param zNear
     * @param zFar
     * @return
     */
    Matrix4f initPerpectiveProjection(float FOV, float WIDTH, float HEIGHT,
                                    float zNear, float zFar);

    /**
     * Initializes Orthographic Projection Matrix
     * @param width
     * @param height
     * @param zNear
     * @param zFar
     * @return
     */
    Matrix4f initOrthographicProjection(float width, float height, float zNear, float zFar);

    /**
     * Initializes Orthographic Projection
     * @param left
     * @param right
     * @param top
     * @param bottom
     * @param zNear
     * @param zFar
     * @return
     */
    Matrix4f initOrthographicProjection(float left, float right, float top, float bottom, float zNear, float zFar);

    /**
     * Initializes Camera Matrix
     * @param target
     * @param up
     * @return
     */
    Matrix4f initCamera(const Vector3D& target, const Vector3D& up);

    /**
     * Initializes Camera Matrix with initial Position
     * @param target
     * @param up
     * @param translate
     * @return
     */
    Matrix4f initCamera(const Vector3D& target, const Vector3D& up, Vector3D translate);

    /**
     * Initializes Camera Matrix with Initial Position
     * @param target
     * @param up
     * @param view
     * @param translate
     * @return
     */
    Matrix4f initCamera(const Vector3D& target, const Vector3D& up, const Vector3D& view, Vector3D translate);

    Matrix4f operator*(const Matrix4f& right)const;
    Vector3D operator*(const Vector3D& vec)const;

    /**
     * Consolidated Point based off Matrix
     * @return
     */
    Vector4D toVector4()const;

    /**
     * Transposes the Matrix.
     * @return Transposed Matrix.
     */
    const Matrix4f transpose()const;

    /**
     * Info about the Matrix;
     * @return
     */
    std::string getInfo();

    void save(std::ofstream& out){
        out.write((char*)&m, sizeof(m));
    }

    void load(std::ifstream& in){
        in.read((char*)&m, sizeof(m));
    }

    stReal m[4][4];
};

#endif //WAHOO_MATRIX_H
