#include "Camera.h"

Camera::Camera() {
    start = false;
    m_Width = 0;
    m_Height = 0;
}

Camera::Camera(STechWindow &win, Vector3<stReal> &pos, ViewProfile &viewProfile) {
    start = false;
    m_Width = (float)win.getWidth();
    m_Height = (float)win.getHeight();

    m_transform.setTranslate(pos);
    m_viewProf = viewProfile;
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
