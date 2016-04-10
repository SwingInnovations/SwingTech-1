#include "Camera.h"

Camera::Camera() {
    start = false;
    m_Width = 0;
    m_Height = 0;
}

Camera::Camera(STGame &win, Vector3<stReal> &pos, ViewProfile &viewProfile) {
    start = false;
    m_Width = (float)win.getWidth();
    m_Height = (float)win.getHeight();

    m_transform.setTranslate(pos);
    m_viewProf = viewProfile;
    m_Forward = Vector3<stReal>(1.0f, 0.0f, 0.0f);
    m_Up = Vector3<stReal>(0.0f, 1.0f, 0.0f);
    hAngle = 0.0f;
    vAngle = 0.0f;
}

Camera::Camera(STGame &win, Vector3<stReal> &pos, int presetMode) {
    start = false;
    m_Width = (float)win.getWidth();
    m_Height = (float)win.getHeight();
    m_transform.setTranslate(pos);
    m_Forward = Vector3<stReal>(1.0f, 0.0f, 0.0f);
    m_Up = Vector3<stReal>(0.0f, 1.0f, 0.0f);
    if(presetMode == DefaultView_PERSP){
        ViewProfile viewProfile;
        viewProfile.FOV = 33.0f;
        viewProfile.moveMode = CAMERA_MOVEMENT::FIRST_PERSON;
        viewProfile.viewMode = CAMERA_VIEW::PERSPECTIVE;
        viewProfile.zNear = 1.0f;
        viewProfile.zFar = 100.0f;
        m_viewProf = viewProfile;
        win.getInput()->setCursorBound(true);
        win.getInput()->centerMouseInWindow();
        win.getInput()->setCursorVisible(false);
    }
    hAngle = 0.0f;
    vAngle = 0.0f;
}

void Camera::update() {
    Vector3<stReal> vAxis(0.0f, 1.0f, 0.0f);

    m_View = Vector3<stReal>(1.0f, 0.0f, 0.0f);
    m_View.rotate(hAngle, vAxis);
    m_View.normalize();

    Vector3<stReal> hAxis = vAxis.cross(m_View);
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
            stReal x = transform()->getTranslate<stReal>().getX();
            stReal y = transform()->getTranslate<stReal>().getY();
            stReal z = transform()->getTranslate<stReal>().getZ();
            x -= m_Forward.getX() * 0.0005f * delta;
            y -= m_Forward.getY() * 0.0005f * delta;
            z -= m_Forward.getZ() * 0.0005f * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateY(y);
            transform()->setTranslateZ(z);
        }
        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::BACKWARD))){
            stReal x = transform()->getTranslate<stReal>().getX();
            stReal y = transform()->getTranslate<stReal>().getY();
            stReal z = transform()->getTranslate<stReal>().getZ();
            x += m_Forward.getX() * 0.0005f * delta;
            y += m_Forward.getY() * 0.0005f * delta;
            z += m_Forward.getZ() * 0.0005f * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateY(y);
            transform()->setTranslateZ(z);
        }
        Vector3<stReal> right = m_Forward.cross(m_Up);
        right.normalize();
        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::STRAFE_LEFT))){
            stReal x = transform()->getTranslate<stReal>().getX();
            stReal z = transform()->getTranslate<stReal>().getZ();

            x -= right.getX() * 0.0005f * delta;
            z -= right.getZ() * 0.0005f * delta;
            transform()->setTranslateX(x);
            transform()->setTranslateZ(z);
        }

        if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::STRAFE_RIGHT))){
            stReal x = transform()->getTranslate<stReal>().getX();
            stReal z = transform()->getTranslate<stReal>().getZ();

            x += right.getX() * 0.0005f * delta;
            z += right.getZ() * 0.0005f * delta;
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
    if(!start){
        Vector3<stReal> vAxis( (stReal)0.0f, (stReal)1.0f, (stReal)0.0f );

        m_View = Vector3<stReal>((stReal)1.0f, (stReal)0.0f, (stReal)0.0f);
        m_View.rotate(hAngle, vAxis);
        m_View.normalize();

        Vector3<stReal> hAxis = vAxis.cross(m_View);
        hAxis.normalize();
        m_View.rotate(vAngle, hAxis);

        m_Forward = m_View;
        m_Forward.normalize();

        m_Up = m_Forward.cross(hAxis);
        m_Up.normalize();
        start = true;
    }else{
        if(input->isCursorBound()){
            hAngle -= input->getMouseSensitivity() * ((m_Width/2) - input->getMouseCoords<int>().getX());
            vAngle -= input->getMouseSensitivity() * ((m_Height/2) - input->getMouseCoords<int>().getY());
        }

        Vector3<stReal> vAxis(0.0f, 1.0f, 0.0f);

        m_View = Vector3<stReal>(1.0f, 0.0f, 0.0f);
        m_View.rotate(hAngle, vAxis);
        m_View.normalize();

        Vector3<stReal> hAxis = vAxis.cross(m_View);
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
    TransformTranslate.initTranslation(m_transform.getTranslate<stReal>());
    View = ViewMode * Camera * TransformTranslate;
    return View;
}

Matrix4f Camera::getView() const {
    Matrix4f Camera, TransformTranslate;
    Camera.initCamera(m_Forward, m_Up);
    TransformTranslate.initTranslation(m_transform.getTranslate<stReal>());
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