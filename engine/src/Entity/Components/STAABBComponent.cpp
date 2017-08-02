#include "STAABBComponent.h"
#include "../STEntity.h"
#include "STEventComponent.h"

STAABBComponent::STAABBComponent() {

}

void STAABBComponent::init(STEntity *parent) {
    this->parent = parent;
    calculateBounds();
}

STAABBComponent::STAABBComponent(STEntity *parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint) {
    this->parent = parent;
    calculateBounds();
    m_MinPoint = minPoint;
    m_MaxPoint = maxPoint;
    m_CalcMinPt = m_MinPoint;
    m_CalcMaxPt = m_MaxPoint;
}

void STAABBComponent::calculateBounds() {
    auto vertex = parent->get<STMeshComponent>()->getMesh()->getMeshStructure().m_vertices;
    auto transform = parent->transform()->getModel();
    m_MinPoint = m_MaxPoint = parent->transform()->getTranslate();
    for (auto &v : vertex) {
        m_MinPoint = Vector3<stReal>::Min(m_MinPoint, transform * *v.getVertex());
        m_MaxPoint = Vector3<stReal>::Max(m_MaxPoint, transform * *v.getVertex());
    }
}

void STAABBComponent::update() {
    calculateBounds();
}




