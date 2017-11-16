#ifndef WAHOO_STLIGHT_H
#define WAHOO_STLIGHT_H

#include "../Math/STCore.h"
#include "../Math/Vector.h"
#include "Transform.h"
#include "STEntity.h"
#include "../Graphics/STMaterial.h"
#include "../Graphics/GL/GLShader.h"
#include "Components/STGraphicsComponent.h"
#include "Components/STMeshComponent.h"
#include "Components/STEventComponent.h"
#include "Components/STLightComponent.h"
#include "Components/STShadowComponent.h"


class STLight :public STEntity{
public:

    /**
     * Initializes a Directional Light.
     * @param position  Position in scene
     * @param direction Direction light is aimed towards
     * @param color     Color of light
     * @return new STLight
     */
    static STLight* InitDirectionalLight(Vector3<stReal> position, Vector3<stReal> direction, Vector3<stReal> color);

    static STLight* InitSpotLight(Vector3<stReal> position, Vector3<stReal> direction, Vector3<stReal> color, stReal coneAngle, stReal coneDistance);

    static STLight* InitPointLight(Vector3<stReal> position, Vector3<stReal> color, stReal radius);

    STLight();

    ~STLight();

    bool isDebug(){ return m_debug; }
    bool setDebug(bool value){
        this->m_debug = value;
    }

    stUint shadowMapID[6]{};
    stUint shadowFrameBuffer[6]{};
    Matrix4f projections[6];
private :
    STMaterial* m_material{};
    bool m_debug{};
};




#endif //WAHOO_STLIGHT_H
