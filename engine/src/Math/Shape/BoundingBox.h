#ifndef SWINGTECH1_BOUNDINGBOX_H
#define SWINGTECH1_BOUNDINGBOX_H


#include "../STCore.h"
#include "../Vector.h"
#include "../../Entity/Transform.h"

class Transform;

class STBoundingBox{
public:
    /**
     * Default Constructor.
     * Initializes Minimum and Maximum Points of the Bounding Box
     */
    STBoundingBox(){
        m_extMinPoint = Vector3D(0.f, 0.f, 0.f);
        m_extMaxPoint = Vector3D(0.f, 0.f, 0.f);
    }

    /**
     * Copy Constructor
     * @param copy
     */
    STBoundingBox(const STBoundingBox& copy){
        this->m_extMinPoint = copy.m_extMinPoint;
        this->m_extMaxPoint = copy.m_extMaxPoint;
    }

    /**
     * Initializes a Bounding box with the specified minimum and maximium points
     * @param minPoint
     * @param maxPoint
     */
    explicit STBoundingBox(const Vector3<stReal>& minPoint, const Vector3<stReal>& maxPoint){
        this->m_extMinPoint = minPoint;
        this->m_extMaxPoint = maxPoint;
    }

    /**
     * Sets the Minimum and Maximum Points based on a center point and extents.
     * @param centerPoint
     * @param extants
     */
    void setDimensions(const Vector3<stReal>& centerPoint, const Vector3<stReal>& extants){
        this->m_extMinPoint = centerPoint - extants;
        this->m_extMaxPoint = centerPoint + extants;
    }

    void update(const Transform& transform){
        //Should be updating with transform
		m_originPoint = transform.getTranslate();
		m_transformedMinPoint = transform.getModel() * m_extMinPoint;
		m_transformedMaxPoint = transform.getModel() * m_extMaxPoint;
    }

    /**
     * Sets the Min point of Bounding Box
     * @param minPoint
     */
    void setMinPoint(const Vector3<stReal>& minPoint){ this->m_extMinPoint = minPoint; }
    /**
     * Sets the Max point of Bounding Box
     * @param maxPoint
     */
    void setMaxPoint(const Vector3<stReal>& maxPoint){ this->m_extMaxPoint = maxPoint; }

    /**
     * Returns the bounding box's minimum point;
     * @return
     */
    Vector3<stReal> getMinPoint()const{ return m_extMinPoint; }

    /**
     * Returns the bounding box's maximum point.
     * @return
     */
    Vector3<stReal> getMaxPoint()const{ return m_extMaxPoint; }

    /**
     * Checks if bounding box contains point.
     * @param point
     * @return
     */
    bool contains(const Vector3<stReal> point){
        return (point >= m_extMinPoint) && (point <= m_extMaxPoint);
    }

    /**
     * Returns the origin point.
     * @return
     */
    Vector3<stReal> getOriginPoint()const {
        stReal hX = (m_extMaxPoint.getX() + m_extMinPoint.getX()) / 2;
        stReal hY = (m_extMaxPoint.getY() + m_extMinPoint.getY()) / 2;
        stReal hZ = (m_extMaxPoint.getZ() + m_extMinPoint.getZ()) / 2;
        return Vector3<stReal>(hX, hY, hZ);
    }

    /**
     * Returns the extents(half dimensions) of the bounding box.
     * @return
     */
    Vector3<stReal> getExtants()const{
        auto h_dX = sqrtf((stReal)pow(m_extMaxPoint.getX() - m_extMinPoint.getX(), 2));
        auto h_dY = sqrtf((stReal)pow(m_extMaxPoint.getY() - m_extMinPoint.getY(), 2));
        auto h_dZ = sqrtf((stReal)pow(m_extMaxPoint.getZ() - m_extMinPoint.getZ(), 2));
        return Vector3<stReal>(h_dX, h_dY, h_dZ);
    }


private:
	Vector3D m_transformedMinPoint;	//After transformations
	Vector3D m_transformedMaxPoint;	//After transformations
    Vector3D m_extMinPoint;
    Vector3D m_extMaxPoint;
	Vector3D m_originPoint;			//Location in world space
};

#endif //SWINGTECH1_BOUNDINGBOX_H
