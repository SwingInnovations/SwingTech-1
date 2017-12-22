#include "Camera.h"
#include "../Application/STGame.h"

Camera::Camera() {
    m_start = false;
    m_transform = new Transform;
    m_Width = 0;
    m_Height = 0;
}

Camera::Camera(STGame &win, Vector3D &pos, ViewProfile &viewProfile) {
    m_start = false;
    m_Width = (float)win.getWidth();
    m_Height = (float)win.getHeight();

    m_transform = new Transform();
    m_transform->setTranslate(pos);
    m_viewProf = viewProfile;
    m_Forward = Vector3D(1.0f, 0.0f, 0.0f);
    m_Up = Vector3D(0.0f, 1.0f, 0.0f);
    hAngle = 0.0f;
    vAngle = 0.0f;
}

Camera::Camera(STGame &win, Vector3D pos, int presetMode) {
    m_start = false;
    m_Width = (float)win.getWidth();
    m_Height = (float)win.getHeight();
    m_transform = new Transform();
    m_transform->setTranslate(pos);
    m_Forward = Vector3D(0.0f, 0.0f, 1.0f);
    m_Up = Vector3D(0.0f, 1.0f, 0.0f);
    m_Speed = 0.05f;
    ViewProfile viewProfile;
    if(presetMode == DefaultView_PERSP){
        viewProfile.FOV = 45.0f;
        viewProfile.moveMode = CAMERA_MOVEMENT::FIRST_PERSON;
        viewProfile.viewMode = CAMERA_VIEW::PERSPECTIVE;
        viewProfile.zNear = 1.0f;
        viewProfile.zFar = 100.0f;
        m_viewProf = viewProfile;
        win.getInput()->setCursorBound(true);
        win.getInput()->centerMouseInWindow();
        win.getInput()->setCursorVisible(false);
    }else if(presetMode == DefaultView_ORTHO){
        viewProfile.FOV = 45;
        viewProfile.moveMode = CAMERA_MOVEMENT::LOCKED;
        viewProfile.viewMode = CAMERA_VIEW::ORTHOGRAPHIC;
        viewProfile.zNear = 1.0f;
        viewProfile.zFar = 100.0f;
        m_viewProf = viewProfile;
        win.getInput()->setCursorBound(false);
        win.getInput()->setCursorVisible(true);
    }
    hAngle = 0.0f;
    vAngle = 0.0f;
}

void Camera::init(ViewProfile viewProfile) {
    m_viewProf= viewProfile;
    m_start = false;
    m_Forward = Vector3D(0.0f, 0.0f, 1.0f);
    hAngle = 0.0f;
    vAngle = 0.0f;
}

void Camera::update() {
    Vector3D vAxis(0.0f, 1.0f, 0.0f);

    m_View = Vector3D(0.0f, 0.0f, 1.0f);
    m_View.rotate(hAngle, vAxis);
    m_View.normalize();

    Vector3D hAxis = vAxis.cross(m_View);
    hAxis.normalize();
    m_View.rotate(vAngle, hAxis);

    m_Forward = m_View;
    m_Forward.normalize();

    m_Up = m_Forward.cross(hAxis);
    m_Up.normalize();
}

void Camera::update(Input* input) {
    if(m_viewProf.moveMode == CAMERA_MOVEMENT::FIRST_PERSON){
        processFPS(input);

        auto delta = input->getDelta();
        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::FORWARD))){
            stReal x = transform()->getTranslate().getX();
            stReal y = transform()->getTranslate().getY();
            stReal z = transform()->getTranslate().getZ();
            x += m_Forward.getX() * m_Speed * delta;
            y -= m_Forward.getY() * m_Speed * delta;
            z += m_Forward.getZ() * m_Speed * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateY(y);
            transform()->setTranslateZ(z);
        }
        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::BACKWARD))){
            stReal x = transform()->getTranslate().getX();
            stReal y = transform()->getTranslate().getY();
            stReal z = transform()->getTranslate().getZ();
            x -= m_Forward.getX() * m_Speed * delta;
            y += m_Forward.getY() * m_Speed * delta;
            z -= m_Forward.getZ() * m_Speed * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateY(y);
            transform()->setTranslateZ(z);
        }
        Vector3<stReal> right = m_Forward.cross(m_Up);
        right.normalize();
        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::STRAFE_LEFT))){
            stReal x = transform()->getTranslate().getX();
            stReal z = transform()->getTranslate().getZ();

            x += right.getX() * m_Speed * delta;
            z += right.getZ() * m_Speed * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateZ(z);
        }

        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::STRAFE_RIGHT))){
            stReal x = transform()->getTranslate().getX();
            stReal z = transform()->getTranslate().getZ();

            x -= right.getX() * m_Speed * delta;
            z -= right.getZ() * m_Speed * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateZ(z);
        }
    }

}

void Camera::centerCam(Input* input) {
    input->centerMouseInWindow();
    hAngle = 0.0f;
    vAngle = 0.0f;
}

void Camera::setHAngle(const stReal _h) {
    hAngle = _h;
}

void Camera::setVAngle(const stReal _v) {
    vAngle = _v;
}

void Camera::processFPS(Input *input) {
    if(!m_start){
        Vector3D vAxis(0.0f, 1.0f, 0.0f );

        m_View = Vector3D(1.0f, 0.0f, 0.0f);
        m_View.rotate(hAngle, vAxis);
        m_View.normalize();

        Vector3D hAxis = vAxis.cross(m_View);
        hAxis.normalize();
        m_View.rotate(vAngle, hAxis);

        m_Forward = m_View;
        m_Forward.normalize();

        m_Up = m_Forward.cross(hAxis);
        m_Up.normalize();
        m_start = true;
    }else{
        if(input->isCursorBound()){
            hAngle -= input->getMouseSensitivity() * ((m_Width/2) - input->getMouseCoords().getX());
            vAngle -= input->getMouseSensitivity() * ((m_Height/2) - input->getMouseCoords().getY());
        }

        Vector3D vAxis(0.0f, 1.0f, 0.0f);

        m_View = Vector3D(1.0f, 0.0f, 0.0f);
        m_View.rotate(hAngle, vAxis);
        m_View.normalize();

        Vector3D hAxis = vAxis.cross(m_View);
        hAxis.normalize();
        m_View.rotate(vAngle, hAxis);

        m_Forward = m_View;
        m_Forward.normalize();

        m_Up = m_Forward.cross(hAxis);
        m_Up.normalize();

        if(input->isCursorBound()){
            input->centerMouseInWindow();
        }
    }
}

Matrix4f Camera::getViewProjection() const {
    Matrix4f View, Camera, ViewMode, TransformTranslate;
    if(m_viewProf.viewMode == CAMERA_VIEW::PERSPECTIVE){
        ViewMode.initPerpectiveProjection(m_viewProf.FOV, m_Width, m_Height, m_viewProf.zNear, m_viewProf.zFar);
    }else{
        ViewMode.initOrthographicProjection(m_Width, m_Height, m_viewProf.zNear, m_viewProf.zFar);
    }

    Camera.initCamera(m_Forward, m_Up);
    TransformTranslate.initTranslation(m_transform->getTranslate());
    View = ViewMode * Camera * TransformTranslate;
    return View;
}

Matrix4f Camera::getView() const {
    Matrix4f Camera, TransformTranslate;
    Camera.initCamera(m_Forward, m_Up);
    auto transVec = m_transform->getTranslate();
    TransformTranslate.initTranslation(-transVec.getX(), transVec.getY(), -transVec.getZ());
    return Camera * TransformTranslate;
}

Matrix4f Camera::getProjection() const {
    Matrix4f ViewMode;
    if(m_viewProf.viewMode == CAMERA_VIEW::PERSPECTIVE){
        ViewMode.initPerpectiveProjection(m_viewProf.FOV, m_Width, m_Height, m_viewProf.zNear
        , m_viewProf.zFar);
    }else{
        ViewMode.initOrthographicProjection(m_Width, m_Height, m_viewProf.zNear
        , m_viewProf.zFar);
    }
    return ViewMode;
}

Camera::~Camera() {
    delete m_transform;
}
