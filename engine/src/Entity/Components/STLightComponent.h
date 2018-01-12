#ifndef SWINGTECH1_STLIGHTCOMPONENT_H
#define SWINGTECH1_STLIGHTCOMPONENT_H

#include "STComponent.h"
#include "../STEntity.h"

#include <cereal/archives/binary.hpp>

struct STLightProperties{
    Vector4<stReal> direction = Vector4<stReal>(0.f, 0.f, 0.f, 0.f);//4th component determines type. -1 for pointlights, 0 for directional, 1 for spotlight     //Specify the target.
    Vector3<stReal> color = Vector3<stReal>(1.f, 1.f, 1.f);
    Vector2<stReal> spotLightAtribs = Vector2<stReal>(0.f, 0.f);    //Encode Light Attributes 0- ConeAngle, 1- coneHeight
    stReal intensity = 0.5f;
    stReal radius = -0.1f;
    int useShadow = 0;
    Vector3<stReal> target = Vector3<stReal>(0, 0, 0);
    /**
     * Calculates the direction Vector
     * @return
     */
    Vector4<stReal> CalculateDirection(Vector3<stReal> position){
        stReal state = direction.getW();
        Vector3<stReal> dir = (position - target);
        dir.normalize();
        direction = Vector4<stReal>(dir.getX(), dir.getY(), dir.getZ(), state);
        return direction;
    }
    template<class Archive> void serialize(Archive& ar){
        ar(direction, color, spotLightAtribs, intensity, radius, useShadow, target);
    }
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

    STLightComponent(){
        m_hasTarget = false;
    }
    STLightComponent(STLightProperties prop) {
        this->m_Properties = prop;
    }

    void setType(LIGHT_TYPE type){
        this->m_type = type;
    }

    void setTarget(Vector3<stReal> target){
        getProperties()->target = target;
        m_hasTarget = true;
    }

    LIGHT_TYPE getType(){   return this->m_type; }

    void update() {

    }

    void draw(){

    }

    template<class Archive> void serialize(Archive& ar);

    STLightProperties* getProperties(){ return &m_Properties; }
    Matrix4f getLookAt(){
        auto props = this->getProperties();
        Vector3<stReal> dir = (m_entity->transform()->getTranslate() - props->target);
        if(m_hasTarget){
            return Matrix4f::LookAt(m_entity->transform()->getTranslate(),
                                    dir.normalize(),
                                    Vector3<stReal>(0.f, 1.f, 0.f));
        }
        auto normDir = props->direction.toVector3().normalize();
        return Matrix4f::LookAt(m_entity->transform()->getTranslate(),
                                normDir,
                                Vector3<stReal>(0.f, 1.f, 0.f));
    }
private:
    LIGHT_TYPE m_type;
    STLightProperties m_Properties;
    bool m_hasTarget;
};

template<class Archive>
void STLightComponent::serialize(Archive &ar) {
    ar(m_type, m_Properties);
}

#endif //SWINGTECH1_STLIGHTCOMPONENT_H
