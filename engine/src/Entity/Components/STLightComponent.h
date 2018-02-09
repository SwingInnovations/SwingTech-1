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
    Vector3<stReal> target = Vector3D(0, 0, 0);

    STLightProperties() = default;
    STLightProperties(const STLightProperties& other){
        direction = other.direction;
        color = other.color;
        spotLightAtribs = other.spotLightAtribs;
        intensity = other.intensity;
        radius = other.radius;
        useShadow = other.useShadow;
        target = other.target;
    }

    void load(std::ifstream& in){
        direction.load(in);
        color.load(in);
        spotLightAtribs.load(in);
        target.load(in);
        in.read((char*)&intensity, sizeof(stReal));
        in.read((char*)&radius, sizeof(stReal));
        in.read((char*)&useShadow, sizeof(int));
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
    ~STLightComponent() override ;
    explicit STLightComponent(STLightProperties prop) {
        m_Properties = prop;
        m_type = DIRECTIONAL_LIGHT;
        m_hasTarget = false;
    }

    void setType(LIGHT_TYPE type){
        this->m_type = type;
    }

    void setTarget(Vector3<stReal> target);
    LIGHT_TYPE getType() const {   return this->m_type; }

    void update() override {
        ;
    }

    void save(std::ofstream& out) override;

    void load(std::ifstream& in) override;

    STLightProperties* getProperties();
    Matrix4f getLookAt();
private:
    LIGHT_TYPE m_type;
    STLightProperties m_Properties;
    bool m_hasTarget;
};


#endif //SWINGTECH1_STLIGHTCOMPONENT_H
