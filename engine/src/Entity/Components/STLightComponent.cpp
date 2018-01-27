#include "STLightComponent.h"

void STLightComponent::setTarget(Vector3<stReal> target) {
    getProperties()->target = target;
    m_hasTarget = true;
}

void STLightComponent::save(std::ofstream &out) {
    m_Properties.save(out);
    out.write((char*)&m_type, sizeof(m_type));
    out.write((char*)&m_hasTarget, sizeof(bool));
}

void STLightComponent::load(std::ifstream &in) {
    m_Properties.load(in);
    in.read((char*)&m_type, sizeof(m_type));
    in.read((char*)&m_hasTarget, sizeof(bool));
}

STLightComponent::STLightComponent() {
    m_hasTarget = false;
    m_Properties = STLightProperties();
}

STLightComponent::STLightComponent(const STLightComponent &copy) {

}
