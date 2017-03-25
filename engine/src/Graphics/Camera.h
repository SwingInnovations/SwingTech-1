#ifndef WAHOO_CAMERA_H
#define WAHOO_CAMERA_H

#include "../STGlobal.h"

class Transform;
class Matrix4f;
class Input;

struct ViewProfile{
    ViewProfile(){
        this->FOV = 0.0;
        this->zNear = 0.0f;
        this->zFar = 0.0f;
        this->viewMode = 0;
        this->moveMode = 0;
    }

    ViewProfile(float _fov, float _zNear, float _zFar, int _viewMode, int _moveMode){
        this->FOV = _fov;
        this->zFar = _zFar;
        this->zNear = _zNear;
        this->viewMode = _viewMode;
        this->moveMode = _moveMode;
    }

    float FOV = 0.0f;
    float zNear = 0.0f;
    float zFar = 0.0f;
    int viewMode = 0;
    int moveMode = 0;
};

namespace CAMERA_VIEW{
  enum MODE{
    PERSPECTIVE = 0,
      ORTHOGRAPHIC = 1
  };
};

namespace CAMERA_MOVEMENT{
    enum MODE{
    FIRST_PERSON = 0,
        THIRD_PERSON = 1,
        ISOMETRIC = 2,
        LOCKED = 3
    };
};

class Camera {
public:
    Camera();
    Camera(STGame &, Vector3<stReal>&, ViewProfile&);
    Camera(STGame &, Vector3<stReal>&, int);

    /*!
     *
     * @param viewProfile Viewprofile to define the camera.
     */
    void init(ViewProfile viewProfile);
    void update();
    void update(Input* input);

    void centerCam(Input* input);

    /*!
     * @name
     * @param _h Horizontal rotation in radians.
     */
    void setHAngle(const stReal _h);
    /*!
     *
     * @param _v Vertical Rotation in radians.
     */
    void setVAngle(const stReal _v);

    inline ViewProfile* viewProf(){ return &m_viewProf; }
    inline Transform* transform(){ return &m_transform; }

    inline void setSpeed(stReal speed){this->m_Speed = speed;}

    inline stReal getHAngle(){ return hAngle; }
    inline stReal getVAngle(){ return vAngle; }
    inline stReal getSpeed()const{ return m_Speed; }

    /*!
     *
     * @return Returns the combined view projection matrix.
     */
    Matrix4f getViewProjection() const;
    Matrix4f getView() const;
    Matrix4f getProjection() const;

    Vector3<stReal> getForward()const{ return m_Forward; }
    Vector3<stReal> getUp()const{ return m_Up; }
private:
    void processFPS(Input* input);
    Transform m_transform;
    bool m_start;

    Vector3<stReal> m_Forward;
    Vector3<stReal> m_Up;
    Vector3<stReal> m_View;

    stReal hAngle;
    stReal vAngle;

    stReal m_Speed;

    float m_Width, m_Height;
    ViewProfile m_viewProf;
    enum{
        DefaultView_PERSP = 0,
        DefaultView_ORTHO = 1
    };
};


#endif //WAHOO_CAMERA_H
