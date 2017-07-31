#ifndef SWINGTECH1_BOUNDINGBOX_H
#define SWINGTECH1_BOUNDINGBOX_H

#include "../STCore.h"
#include "../Vector.h"

class STBoundingBox{
public:
    /**
     * Default Constructor.
     * Initializes Minimum and Maximum Points of the Bounding Box
     */
    STBoundingBox(){
        minPoint = Vector3<stReal>(0.f, 0.f, 0.f);
        maxPoint = Vector3<stReal>(0.f, 0.f, 0.f);
    }

    /**
     * Copy Constructor
     * @param copy
     */
    STBoundingBox(const STBoundingBox& copy){
        this->minPoint = copy.minPoint;
        this->maxPoint = copy.maxPoint;
    }

    /**
     * Initializes a Bounding box with the specified minimum and maximium points
     * @param minPoint
     * @param maxPoint
     */
    explicit STBoundingBox(const Vector3<stReal>& minPoint, const Vector3<stReal>& maxPoint){
        this->minPoint = minPoint;
        this->maxPoint = maxPoint;
    }

    /**
     * Sets the Minimum and Maximum Points based on a center point and extents.
     * @param centerPoint
     * @param extants
     */
    void setDimensions(const Vector3<stReal>& centerPoint, const Vector3<stReal>& extants){
        this->minPoint = centerPoint - extants;
        this->maxPoint = centerPoint + extants;
    }

    /**
     * Sets the Min point of Bounding Box
     * @param minPoint
     */
    void setMinPoint(const Vector3<stReal>& minPoint){ this->minPoint = minPoint; }
    /**
     * Sets the Max point of Bounding Box
     * @param maxPoint
     */
    void setMaxPoint(const Vector3<stReal>& maxPoint){ this->maxPoint = maxPoint; }

    /**
     * Returns the bounding box's minimum point;
     * @return
     */
    Vector3<stReal> getMinPoint()const{ return minPoint; }

    /**
     * Returns the bounding box's maximum point.
     * @return
     */
    Vector3<stReal> getMaxPoint()const{ return maxPoint; }

    /**
     * Checks if bounding box contains point.
     * @param point
     * @return
     */
    bool contains(const Vector3<stReal> point){
        return (point.getX() < maxPoint.getX())
               && (point.getY() < maxPoint.getY())
               && (point.getZ() < maxPoint.getZ())
               && (point.getX() > minPoint.getX())
               && (point.getY() > minPoint.getY())
               && (point.getZ() > minPoint.getZ());
    }

    /**
     * Returns the origin point.
     * @return
     */
    Vector3<stReal> getOriginPoint()const {
        stReal hX = (maxPoint.getX() + minPoint.getX()) / 2;
        stReal hY = (maxPoint.getY() + minPoint.getY()) / 2;
        stReal hZ = (maxPoint.getZ() + minPoint.getZ()) / 2;
        return Vector3<stReal>(hX, hY, hZ);
    }

    /**
     * Returns the extents(half dimensions) of the bounding box.
     * @return
     */
    Vector3<stReal> getExtants()const{
        auto h_dX = sqrtf((stReal)pow(maxPoint.getX() - minPoint.getX(), 2));
        auto h_dY = sqrtf((stReal)pow(maxPoint.getY() - minPoint.getY(), 2));
        auto h_dZ = sqrtf((stReal)pow(maxPoint.getZ() - minPoint.getZ(), 2));
        return Vector3<stReal>(h_dX, h_dY, h_dZ);
    }

private:
    Vector3<stReal> minPoint;
    Vector3<stReal> maxPoint;
};

#endif //SWINGTECH1_BOUNDINGBOX_H
