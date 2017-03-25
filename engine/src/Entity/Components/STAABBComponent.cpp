#include "STAABBComponent.h"
#include "../STEntity.h"

STAABBComponent::STAABBComponent(STEntity *parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint) {
    m_Entity = parent;
    m_MinPoint = minPoint;
    m_MaxPoint = maxPoint;
    m_CalcMinPt = m_MinPoint;
    m_CalcMaxPt = m_MaxPoint;
}


void STAABBComponent::update() {

}

void STAABBComponent::adjustTransX(stReal x) {
    m_MinPoint.setX(m_MinPoint.getX() + x);
    m_MaxPoint.setX(m_MaxPoint.getX() + x);
}

void STAABBComponent::adjustTransY(stReal y) {
    m_MinPoint.setY(m_MinPoint.getX() + y);
    m_MaxPoint.setY(m_MaxPoint.getX() + y);
}

void STAABBComponent::adjustTransZ(stReal z) {
    m_MinPoint.setZ(m_MinPoint.getX() + z);
    m_MaxPoint.setZ(m_MaxPoint.getX() + z);
}

void STAABBComponent::reconstructBounds() {
    Vector3<stReal> points[8];
    points[0] = Vector3<stReal>(m_MinPoint.getX(), m_MinPoint.getY(), m_MinPoint.getZ());
    points[1] = Vector3<stReal>(m_MinPoint.getX() + m_MaxPoint.getX(), m_MinPoint.getY(), m_MaxPoint.getZ());
    points[2] = Vector3<stReal>(m_MinPoint.getX() + m_MaxPoint.getX(), m_MinPoint.getY() + m_MaxPoint.getY(), m_MinPoint.getZ());
    points[3] = Vector3<stReal>(m_MinPoint.getX(), m_MinPoint.getY() + m_MaxPoint.getY(), m_MinPoint.getZ());
    points[4] = Vector3<stReal>(m_MaxPoint.getX(), m_MaxPoint.getY(), m_MaxPoint.getZ());
    points[5] = Vector3<stReal>(m_MaxPoint.getX() - m_MinPoint.getX(), m_MaxPoint.getY(), m_MaxPoint.getZ());
    points[6] = Vector3<stReal>(m_MaxPoint.getX() - m_MinPoint.getX(), m_MaxPoint.getY() - m_MinPoint.getY(), m_MinPoint.getZ());
    points[7] = Vector3<stReal>(m_MaxPoint.getX(), m_MaxPoint.getY() - m_MinPoint.getY(), m_MaxPoint.getZ());
    auto rotateVector = m_Entity->transform()->getRotate<stReal>();
    Matrix4f rot;
    rot.initRotate(rotateVector);
    for(stUint i = 0; i < 8; i++){
        points[i] = rot * points[i];
        m_CalcMinPt = Vector3<stReal>::Min(m_MinPoint, points[i]);
        m_CalcMaxPt = Vector3<stReal>::Max(m_MaxPoint, points[i]);
    }
    std::cout << "Updated Bounds!" << std::endl;
}