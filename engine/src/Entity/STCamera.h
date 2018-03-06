#ifndef SWINGTECH1_STCAMERA_H
#define SWINGTECH1_STCAMERA_H

#include "STEntity.h"
#include "Components/STCameraComponent.h"

class STCamera : public STEntity{
public:
    STCamera();
    //Load from File Implementation
    static std::shared_ptr<STCamera> Create(const std::string& filename);
    static std::shared_ptr<STCamera> Create(STCameraProperties::STViewProfile m_viewProfile, Vector3D startPosition); };


#endif //SWINGTECH1_STCAMERA_H
