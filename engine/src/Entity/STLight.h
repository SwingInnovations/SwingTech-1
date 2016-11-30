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

    enum STLIGHT_TYPE: char
    {
        DirectionalLight,
        PointLight,
        SpotLight
    };

    STLight(Vector3<stReal> direction , Vector3<stReal> color){
        this->direction = Vector4<stReal>(direction, 0.0);
        this->color = color;
        intensity =.5f;
        m_transform = new Transform();
        type = DirectionalLight;
    }

    STLight(stReal radius , Vector3<stReal> color){
        this->radius = radius;
        this->color = color;
        intensity=.5f;
        m_transform = new Transform();
        type = PointLight;
        auto ent = new STEntity("sphere.obj", STMesh::OBJ, new GLShader("LightVis"));
        ent->setShdrUniform("lightColor", color);
        this->addChild(ent);
    }

    STLight(Vector3<stReal> direction, stReal coneAngle , stReal coneHeight){
        this->coneAngle= coneAngle;
        this->coneHeight = coneHeight;
        this->direction = Vector4<stReal>(direction, 1.0);
        intensity=.5f;
        m_transform = new Transform();
        type = SpotLight;
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

    stUint shadowMapID;
    stUint shadowFrameBuffer;
private :
    STMaterial* m_material;
};




#endif //WAHOO_STLIGHT_H
