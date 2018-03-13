#ifndef SWINGTECH1_STCAMERACOMPONENT_H
#define SWINGTECH1_STCAMERACOMPONENT_H

#include <functional>
#include "STComponent.h"
#include "../../Math/STMath.h"

namespace STCameraProperties{
    enum ViewMode : unsigned char{
        PERSPECTIVE = 0,
        ORTHOGRAPHIC = 1
    };

    enum MoveMode : unsigned char{
        FIRST_PERSON = 0,
        FIRST_PERSON_FLY = 1,
        THIRD_PERSON = 2,
        ISOMETRIC = 3,
        LOCKED = 4,
        CUSTOM = 5
    };

    struct STViewProfile{
        stReal FOV = 45.0f;
        stReal zNear = 1.f;
        stReal zFar = 100.f;
        MoveMode m_moveMode = FIRST_PERSON_FLY;
        ViewMode m_viewMode = PERSPECTIVE;
    };
};

class STCameraComponent : public STComponent {
public:
    STCameraComponent() = default;
    STCameraComponent(STCameraProperties::STViewProfile &viewProfile);
    void init(std::shared_ptr<STEntity>& entity) override ;
    void update() override;
    void draw() override;

    /**
     * Sets a custom update Behavior
     * @param customUpdate
     */
    void setCustomUpdate(std::function<void(STCameraComponent*, Input* input)> customUpdate);

    Matrix4f getViewProjection() const;
    Matrix4f getView() const;
    Matrix4f getProjection() const;

    /**
     * Sets Horizontal Rotation
     * @param h
     */
    void setHAngle(stReal h);

    /**
     * Sets Verical Rotation
     * @param v
     */
    void setVAngle(stReal v);

    /**
     * Sets Speed of the Camera
     * @param s
     */
    void setSpeed(stReal s);

    Vector3D getForward() const;
    Vector3D getUp() const;
    void centerCamera(Input* input);

    /**
     * Loads from Serial Stream
     * @param in
     */
    void load(std::ifstream& in) override;

    /**
     * Reads from Serial Stream
     * @param out
     */
    void save(std::ofstream& out) override;
private:
    void        updateCameraRotations(Input* input);
    bool        m_start;    //Starts on First frame
    stReal      m_hAngle;   //Horizontal Rotation
    stReal      m_vAngle;   //Vertical Angle Change

    Vector3D    m_forward;
    Vector3D    m_up;
    Vector3D    m_view;
    stReal      m_speed;

    stUint      m_width, m_height;
    STCameraProperties::STViewProfile   m_viewProfile;
    STCameraProperties::MoveMode        m_moveMode;
    STCameraProperties::ViewMode        m_viewMode;

    std::function<void(STCameraComponent*, Input*)> m_customUpdate;
};


#endif //SWINGTECH1_STCAMERACOMPONENT_H
