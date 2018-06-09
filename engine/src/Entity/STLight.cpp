#include "STLight.h"

std::shared_ptr<STLight> STLight::InitPointLight(Vector3D position, Vector3D color, stReal radius)
{
	auto ret = std::make_shared<STLight>();
	ret->init();
	ret->transform()->setTranslate(position);
	ret->addComponent<STLightComponent>(new STLightComponent);
	ret->addComponent<STShadowComponent>(new STShadowComponent);
	auto lightComp = ret->get<STLightComponent>();
	lightComp->setType(STLightComponent::POINT_LIGHT);
	auto lightProps = lightComp->getProperties();
	lightProps->spotLightAtribs = Vector2D(0.f, 0.f);
	lightProps->radius = radius;
	lightProps->color = color;
	lightProps->direction = Vector4D(0.f, 0.f, 0.f, -1.f);
	lightProps->intensity = 1.0f;
	return ret;
}

std::shared_ptr<STLight> STLight::InitSpotLight(Vector3<stReal> direction, Vector3<stReal> color, stReal coneAngle,
 stReal coneDistance, Vector3<stReal> position) {
	auto ret = std::make_shared<STLight>();
	ret->init();
	ret->addComponent(typeid(STLightComponent), new STLightComponent);
	ret->get<STLightComponent>()->setType(STLightComponent::SPOT_LIGHT);
	ret->addComponent(typeid(STShadowComponent), new STShadowComponent);
	ret->transform()->setTranslate(position);
	auto lightProps = ret->get<STLightComponent>()->getProperties();
	lightProps->spotLightAtribs = Vector2D(coneAngle, coneDistance);
	lightProps->color = color;
	lightProps->direction = Vector4D(direction, 1.0f);
	lightProps->intensity = 1.0f;
	return ret;
}

std::shared_ptr<STLight> STLight::InitDirectionalLight(Vector3<stReal> position, Vector3<stReal> direction, Vector3<stReal> color) {
    auto ret = std::make_shared<STLight>();
    ret->init();
    ret->addComponent(typeid(STLightComponent), new STLightComponent);
    ret->addComponent(typeid(STShadowComponent), new STShadowComponent);
    ret->transform()->setTranslate(position);
    ret->get<STLightComponent>()->setType(STLightComponent::DIRECTIONAL_LIGHT);
    auto lightProps = ret->get<STLightComponent>()->getProperties();
    lightProps->color = color;
    lightProps->spotLightAtribs = Vector2D(0.f, 0.f);
    lightProps->direction = Vector4D(direction, 0.0f);
    lightProps->intensity = 1.f;

    return ret;
}

STLight::STLight() {
    m_type = Light;
}