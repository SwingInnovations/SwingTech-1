#ifndef SWINGTECH1_STLIGHTCOMPONENT_H
#define SWINGTECH1_STLIGHTCOMPONENT_H

#include "../../STGlobal.h"

struct STLightProperies{
    Vector4<stReal> direction = Vector4<stReal>(0.f, 0.f, 0.f, 0.f);          //4th component determines type. -1 for pointlights, 0 for directional, 1 for spotlight
    Vector3<stReal> color = Vector3<stReal>(1.f, 1.f, 1.f);
    Vector2<stReal> spotLightAtribs = Vector2<stReal>(0.f, 0.f);    //Encode Light Attributes 0- ConeAngle, 1- coneHeight
    stReal intensity = 0.5f;
    stReal radius = -0.1f;
    bool useShadow = false;
};

/*
 * @brief Component for Light or Emissive properties.
 */
class STLightComponent : public STComponent{
public:
    enum LIGHT_TYPE: char{
        DIRECTIONAL_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT
    };

    STLightComponent(){;}
    STLightComponent(STLightProperies prop) {
        this->m_Properties = prop;
    }

    void setType(LIGHT_TYPE type){
        this->m_type = type;
    }

    LIGHT_TYPE getType(){   return this->m_type; }

    void update() {

    }

    void draw(){

    }

    STLightProperies* getProperties(){ return &m_Properties; }
private:
    LIGHT_TYPE m_type;
    STLightProperies m_Properties;
};


#endif //SWINGTECH1_STLIGHTCOMPONENT_H
