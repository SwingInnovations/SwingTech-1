#ifndef SWINGTECH1_STLIGHTCOMPONENT_H
#define SWINGTECH1_STLIGHTCOMPONENT_H

#include "../../STGlobal.h"

struct STLightProperies{
    Vector4<stReal> direction;
    Vector3<stReal> color;

    Vector3<stReal> spotLightAtribs;    //Encode Light Attributes 0- Active, 1- ConeAngle, 2- coneHeight

    stReal intensity;
};

/*
 * @brief Component for Light or Emissive properties.
 */
class STLightComponent {
public:
    STLightProperies* getProp(){ return &m_Properties; }
private:
    STLightProperies m_Properties;
};


#endif //SWINGTECH1_STLIGHTCOMPONENT_H
