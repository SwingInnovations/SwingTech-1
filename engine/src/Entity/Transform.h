#ifndef WAHOO_TRANSFORM_H
#define WAHOO_TRANSFORM_H

#include <iostream>

#include "../../include/json11/json11.hpp"

#include "../Math/STCore.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "../Math/Euler.h"

class STEntity;

using namespace json11;

/**
 * @brief Hold Transformation Information.
 */
class Transform{
public:
    /**
     * Rotation Mode
     */
    enum RotationMode: unsigned char {Global = 0, Local = 1};

    static Transform* FromJson(const std::string& jsonFile);
    static Transform* FromJson(const Json doc);

    /**
     * Default Constructor
     * @param parent
     */
    explicit Transform(STEntity* parent);

    Transform();

    /**
     * Instantiates Transform
     * @param translate
     * @param rotate
     * @param scale
     */
    Transform(Vector3D& translate, Vector3D& rotate, Vector3D scale);

    /**
     * @brief Constructor for transform. Sets binding to entity.
     * @param parent        STEntity type
     * @param translate     Initial Position
     * @param rotate        Initial Rotation
     * @param scale         Initial Scale.
     */
    Transform(STEntity* parent, Vector3D& translate, Vector3D& rotate, Vector3D& scale);

    /**
     * Sets position of Transform to Vector3
     * @param vec
     */
    void setTranslate(Vector3D vec);
    void setTranslateX(stReal _x);
    void setTranslateY(stReal _y);
    void setTranslateZ(stReal _z);
    void setTranslate(stReal _value);

    /**
     * Sets Rotation of Transform to Vector3
     * @param vec
     */
    void setRotate(Vector3D vec);
    void setRotateX(stReal _x);
    void setRotateY(stReal _y);
    void setRotateZ(stReal _z);

    /**
     * Sets Scale of Transform to Vector3
     * @param vec
     */
    void setScale(Vector3D vec);
    void setScaleX(stReal _x);
    void setScaleY(stReal _y);
    void setScaleZ(stReal _z);
    void setScale(stReal _value);

    /**
     * Sets Rotation Mode. Either Global or Local.
     * @param rotMode
     */
    void setRotationMode(RotationMode rotMode);

    /**
     * Calculates the final transformation Matrix
     * @return Transformation Matrix
     */
    const Matrix4f getModel()const;

    inline std::string getInfo();

    inline Vector3D getTranslate()const{return translate; }
    inline Vector3D getRotate() const {return rotate;}
    inline Vector3D getScale() const {return scale;}

    Vector3D getForward()const;
    Vector3D getUp()const;
    Vector3D getRight()const;

    Json to_json()const;

    STEntity* getEntity();

private:
    /**
     * Calculates the Forward Right and Up Vectors
     */
    STEntity* parent;
    Vector3D translate;
    Vector3D rotate;
    Vector3D scale;
    RotationMode rotateMode;
};


#endif //WAHOO_TRANSFORM_H
