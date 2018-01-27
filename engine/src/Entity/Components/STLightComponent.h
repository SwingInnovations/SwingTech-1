#ifndef SWINGTECH1_STLIGHTCOMPONENT_H
#define SWINGTECH1_STLIGHTCOMPONENT_H

#include <map>

#include "STComponent.h"
#include "../STEntity.h"

struct STLightProperties{
    Vector4D direction = Vector4D(0.f, 0.f, 0.f, 0.f);//4th component determines type. -1 for pointlights, 0 for directional, 1 for spotlight     //Specify the target.
    Vector3D color = Vector3D(1.f, 1.f, 1.f);
    Vector2D spotLightAtribs = Vector2D(0.f, 0.f);    //Encode Light Attributes 0- ConeAngle, 1- coneHeight
    stReal intensity = 0.5f;
    stReal radius = -0.1f;
    int useShadow = 0;
    Vector3<stReal> target = Vector3<stReal>(0, 0, 0);

    STLightProperties() = default;

    void load(std::ifstream& in){
        direction.load(in);
        color.load(in);
        spotLightAtribs.load(in);
        target.load(in);
        in.read((char*)&intensity, sizeof(stReal));
        in.read((char*)&radius, sizeof(stReal));
        in.read((char*)&useShadow, sizeof(in));
    }

    void save(std::ofstream& out){
        direction.save(out);
        color.save(out);
        spotLightAtribs.save(out);
        target.save(out);
        out.write((char*)&intensity, sizeof(stReal));
        out.write((char*)&radius, sizeof(stReal));
        out.write((char*)&useShadow, sizeof(int));
    }

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

    STLightComponent();
    STLightComponent(const STLightComponent& copy);
    STLightComponent(STLightProperties prop) {
        this->m_Properties = prop;
    }

    void setType(LIGHT_TYPE type){
        this->m_type = type;
    }

    void setTarget(Vector3<stReal> target);

    LIGHT_TYPE getType(){   return this->m_type; }

    void update() {

    }

    void draw(){

    }

    void save(std::ofstream& out) override;

    void load(std::ifstream& in) override;

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


#endif //SWINGTECH1_STLIGHTCOMPONENT_H
