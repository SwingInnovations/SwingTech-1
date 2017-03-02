#ifndef WAHOO_STLIGHT_H
#define WAHOO_STLIGHT_H


#include "../Math/STCore.h"
#include "../Math/Vector.h"
#include "../Math/Transform.h"
#include "../Graphics/STMaterial.h"
#include "../Graphics/GL/GLShader.h"
#include "Components/STGraphicsComponent.h"
#include "Components/STMeshComponent.h"
#include "Components/STEventComponent.h"


class STLight :public STEntity{
public:

    //TODO, Move properties to STLightComponent.
    enum STLIGHT_TYPE: char
    {
        DIRECTIONAL_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT
    };

    // NEW Constructor
    /**
     * Constructs a Directional Light
     * @param direction
     * @param color
     * @return
     */
    static STLight* DirectionalLight(Vector3<stReal> direction, Vector3<stReal> color){
        STLight* ret = new STLight();
        ret->direction = Vector4<stReal>(direction, 0.0);
        ret->color = color;
        ret->type = DIRECTIONAL_LIGHT;
        return  ret;
    }

    /**
     * Constructor for a Directional Light;
     * @param position
     * @param direction
     * @param color
     * @return
     */
    static STLight* DirectionalLight(Vector3<stReal> position, Vector3<stReal> direction, Vector3<stReal> color){
        STLight* ret = new STLight;
        ret->direction = Vector4<stReal>(direction, 0.0);
        ret->setTranslate(position);
        ret->color = color;
        ret->type = DIRECTIONAL_LIGHT;
        return ret;
    }

    // NEW Constructor
    static STLight* SpotLight(Vector3<stReal> direction, Vector3<stReal> color, stReal coneAngle, stReal coneDistance){
        STLight* ret = new STLight();
        ret->direction = Vector4<stReal>(direction, 1.0);
        ret->color = color;
        ret->coneAngle = coneAngle;
        ret->coneHeight = coneDistance;
        ret->type = SPOT_LIGHT;
        return ret;
    }

    // NEW Constructor
    static STLight* Pointlight(stReal radius, Vector3<stReal> color){
        STLight* ret = new STLight;
        ret->radius = radius;
        ret->color = color;
        ret->type = POINT_LIGHT;
        return ret;
    }

    STLight(){
        m_transform = new Transform();
        intensity = 0.5f;
        color = Vector3<stReal>(1.f, 1.f, 1.f);
    }

    // NOTE - This will be Deprecated.
    STLight(Vector3<stReal> direction , Vector3<stReal> color){
        this->direction = Vector4<stReal>(direction, 0.0);
        this->color = color;
        intensity =.5f;
        m_transform = new Transform();
        type = DIRECTIONAL_LIGHT;
    }

    // NOTE - This will be Deprecated.
    STLight(stReal radius , Vector3<stReal> color){
        this->radius = radius;
        this->color = color;
        intensity=.5f;
        m_transform = new Transform();
        type = POINT_LIGHT;
        auto ent = new STEntity("sphere.obj", STMesh::OBJ, new GLShader("LightVis"));
        ent->setShdrUniform("lightColor", color);
        this->addChild(ent);
    }

    // NOTE - This will be Deprecated.
    STLight(Vector3<stReal> direction, stReal coneAngle , stReal coneHeight){
        this->coneAngle= coneAngle;
        this->coneHeight = coneHeight;
        this->direction = Vector4<stReal>(direction, 1.0);
        intensity=.5f;
        m_transform = new Transform();
        type = SPOT_LIGHT;
    }

    ~STLight(){
       delete m_material;
    }

    STLIGHT_TYPE type;

    //Shared Attributes
    Vector4<stReal> position;
    Vector3<stReal> color;
    stReal intensity;


    //Directional Light Attributes
    Vector4<stReal> direction;


    //Point Light Attributes
    stReal radius;

    //Spot Light Attributes
    stReal coneAngle;
    stReal coneHeight;

    stUint shadowMapID[6];
    stUint shadowFrameBuffer[6];
    Matrix4f projections[6];
private :
    STMaterial* m_material;
};




#endif //WAHOO_STLIGHT_H
