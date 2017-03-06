#ifndef SWINGTECH1_STLIGHTCOMPONENT_H
#define SWINGTECH1_STLIGHTCOMPONENT_H

#include "../../STGlobal.h"

struct STLightProperies{
    Vector4<stReal> direction = Vector4<stReal>(0.f, 0.f, 0.f, 0.f);          //4th component determines type. -1 for pointlights, 0 for directional, 1 for spotlight
    Vector3<stReal> color = Vector3<stReal>(1.f, 1.f, 1.f);
    Vector2<stReal> spotLightAtribs = Vector2<stReal>(0.f, 0.f);    //Encode Light Attributes 0- ConeAngle, 1- coneHeight
    stReal intensity = 1.f;
    stReal radius = 1.f;
};

/*
 * @brief Component for Light or Emissive properties.
 */
class STLightComponent : public STComponent{
    enum LIGHT_TYPE: char{
        DIRECTIONAL_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT
    };
public:
    STLightComponent(){;}
    STLightComponent(STLightProperies prop) {
        this->m_Properties = prop;
    }
    void update() {

    }

    void draw(){

    }

    STLightProperies* getProperties(){ return &m_Properties; }
private:
    STLightProperies m_Properties;
};


#endif //SWINGTECH1_STLIGHTCOMPONENT_H
