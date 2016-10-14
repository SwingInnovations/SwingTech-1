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

struct Light{
    Vector4<stReal> position;
    Vector3<stReal> intensity;
    float attenuation;
    float ambientCoefficient;
    float coneAngle;
    Vector3<stReal> coneDirection;
};
enum STLIGHT_TYPE: char
{

    DirectionalLight,
    PointLight,
    SpotLight
};

class STLight :public STEntity{
public:

    STLight(Vector3<stReal> direction , Vector3<stReal> color){
        this->direction = direction;
        this->color = color;
        intensity =.5f;
        m_transform = new Transform();
        //m_material = new STMaterial(new GLShader("standard"));
        //addComponent(typeid(STEventComponent),new STEventComponent());
        //addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(m_material));
        //addComponent(typeid(STMeshComponent), new STMeshComponent());
        type = DirectionalLight;

    }

    STLight(stReal radius , Vector3<stReal> color){
        this->radius = radius;
        this->color = color;
        intensity=.5f;
        m_transform = new Transform();
        //m_material = new STMaterial(new GLShader("standard"));
        //addComponent(typeid(STEventComponent),new STEventComponent());
        //addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(m_material));
        //addComponent(typeid(STMeshComponent), new STMeshComponent());
        type = PointLight;

    }

    STLight(stReal coneAngle , stReal coneHeight){
        this->coneAngle= coneAngle;
        this->coneHeight = coneHeight;
        intensity=.5f;
        m_transform = new Transform();
        //m_material = new STMaterial(new GLShader("standard"));
        //addComponent(typeid(STEventComponent),new STEventComponent());
        //addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(m_material));
        //addComponent(typeid(STMeshComponent), new STMeshComponent());
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
    Vector3<stReal> direction;


    //Point Light Attributes
    stReal radius;

    //Spot Light Attributes
    stReal coneAngle;
    stReal coneHeight;

private :
    STMaterial* m_material;
};




#endif //WAHOO_STLIGHT_H
