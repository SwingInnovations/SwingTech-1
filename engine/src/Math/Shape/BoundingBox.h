#ifndef SWINGTECH1_BOUNDINGBOX_H
#define SWINGTECH1_BOUNDINGBOX_H

#include "../STCore.h"
#include "../Vector.h"

class STBoundingBox{
public:
    STBoundingBox(){
        minPoint = Vector3<stReal>(0.f, 0.f, 0.f);
        maxPoint = Vector3<stReal>(0.f, 0.f, 0.f);
    }

    STBoundingBox(const Vector3<stReal>& minPoint, const Vector3<stReal>& maxPoint){
        this->minPoint = minPoint;
        this->maxPoint = maxPoint;
    }

    void setMinPoint(const Vector3<stReal>& minPoint){ this->minPoint = minPoint; }
    void setMaxPoint(const Vector3<stReal>& maxPoint){ this->maxPoint = maxPoint; }

    Vector3<stReal> getMinPoint()const{ return minPoint; }
    Vector3<stReal> getMaxPoint()const{ return maxPoint; }

    bool contains(const Vector3<stReal> point){
        return (point.getX() < maxPoint.getX())
               && (point.getY() < maxPoint.getY())
               && (point.getZ() < maxPoint.getZ())
               && (point.getX() > minPoint.getX())
               && (point.getY() > minPoint.getY())
               && (point.getZ() > minPoint.getZ());
    }
private:
    Vector3<stReal> minPoint;
    Vector3<stReal> maxPoint;
};

#endif //SWINGTECH1_BOUNDINGBOX_H
