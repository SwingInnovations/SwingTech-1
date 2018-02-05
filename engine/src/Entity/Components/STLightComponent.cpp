#include "STLightComponent.h"

void STLightComponent::setTarget(Vector3<stReal> target) {
    getProperties()->target = target;
    m_hasTarget = true;
}

void STLightComponent::save(std::ofstream &out) {
    m_Properties.save(out);
    out.write((char*)&m_type, sizeof(m_type));
    out.write((char*)&m_hasTarget, sizeof(m_hasTarget));
}

void STLightComponent::load(std::ifstream &in) {
    m_Properties.load(in);
    in.read((char*)&m_type, sizeof(m_type));
    in.read((char*)&m_hasTarget, sizeof(m_hasTarget));
}

STLightComponent::STLightComponent() {
    m_hasTarget = false;
    m_Properties = STLightProperties();
}

STLightComponent::STLightComponent(const STLightComponent &copy) {
    m_Properties = copy.m_Properties;
}

Matrix4f STLightComponent::getLookAt(){
    auto props = getProperties();
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

STLightProperties *STLightComponent::getProperties() { return &m_Properties; }

STLightComponent::~STLightComponent() {

}
