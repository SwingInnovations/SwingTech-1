#ifndef WAHOO_STLIGHT_H
#define WAHOO_STLIGHT_H


#include "Math/STCore.h"
#include "Math/Vector.h"
#include "Math/Transform.h"

struct Light{
    Vector4<stReal> position;
    Vector3<stReal> intensity;
    float attenuation;
    float ambientCoefficient;
    float coneAngle;
    Vector3<stReal> coneDirection;
};

class STLight{
private:
    Transform* m_transform;
};
#endif //WAHOO_STLIGHT_H
