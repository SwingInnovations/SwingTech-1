#ifndef WAHOO_STLIGHT_H
#define WAHOO_STLIGHT_H

#include "../Math/STCore.h"
#include "../Math/Vector.h"
#include "Transform.h"
#include "STEntity.h"
#include "../Graphics/STMaterial.h"
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
    static std::shared_ptr<STLight> InitDirectionalLight(Vector3D position, Vector3D direction, Vector3D color);

    /**
     * Initializes a Spotlight.
     * @param position
     * @param direction
     * @param color
     * @param coneAngle
     * @param coneDistance
     * @return
     */
    static std::shared_ptr<STLight> InitSpotLight(Vector3D direction, Vector3D color, stReal coneAngle, stReal coneDistance, Vector3D position);

    /**
     * Initializes a Point light. Illuminates all directions
     * @param position
     * @param color
     * @param radius
     * @return
     */
    static std::shared_ptr<STLight> InitPointLight(Vector3D position, Vector3D color, stReal radius);

    STLight();
};




#endif //WAHOO_STLIGHT_H
