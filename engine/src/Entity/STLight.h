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

    using STLightPtr = std::shared_ptr<STLight>;
    /**
     * Initializes a Directional Light.
     * @param position  Position in scene
     * @param direction Direction light is aimed towards
     * @param color     Color of light
     * @return new STLight
     */
    static STLightPtr InitDirectionalLight(Vector3D position, Vector3D direction, Vector3D color);

    /**
     * Initializes a Spotlight.
     * @param position
     * @param direction
     * @param color
     * @param coneAngle
     * @param coneDistance
     * @return
     */
    static STLight* InitSpotLight(Vector3D position, Vector3D direction, Vector3D color, stReal coneAngle, stReal coneDistance);

    /**
     * Initializes a Point light. Illuminates all directions
     * @param position
     * @param color
     * @param radius
     * @return
     */
    static STLight* InitPointLight(Vector3D position, Vector3D color, stReal radius);

    STLight();

    ~STLight();

    bool isDebug(){ return m_debug; }
    bool setDebug(bool value){
        this->m_debug = value;
    }
private :
    STMaterial* m_material{};
    bool m_debug{};
};




#endif //WAHOO_STLIGHT_H
