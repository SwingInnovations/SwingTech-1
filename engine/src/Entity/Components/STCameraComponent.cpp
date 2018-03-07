#include "STCameraComponent.h"
#include "../STEntity.h"

STCameraComponent::STCameraComponent(STCameraProperties::STViewProfile &viewProfile) {
    m_viewProfile = viewProfile;
    if(viewProfile.m_moveMode == STCameraProperties::FIRST_PERSON || viewProfile.m_moveMode == STCameraProperties::FIRST_PERSON_FLY){
        auto input = STGame::Get()->getInput();
        input->setCursorVisible(false);
        input->setCursorBound(true);
        input->centerMouseInWindow();
    }
    m_width = (stUint)STGame::Get()->getWidth();
    m_height = (stUint)STGame::Get()->getHeight();
    m_forward  = Vector3D(1.f, 0.f, 0.f);
    m_up = Vector3D(0.f, 1.f, 0.f);
    m_hAngle = 0.f;
    m_vAngle = 0.f;
    m_start = false;
}

void STCameraComponent::init(std::shared_ptr<STEntity>& entity) {
    m_entity = entity;
    if(!m_start){
        Vector3D vAxis(0.f, 1.f, 0.f);

        m_view = Vector3D(1.f, 0.f, 0.f);
        m_view.rotate(m_hAngle, vAxis);
        m_view.normalize();

        Vector3D hAxis = vAxis.cross(m_view);
        hAxis.normalize();
        m_view.rotate(m_vAngle, hAxis);

        m_forward = m_view;
        m_forward.normalize();

        m_up = m_forward.cross(hAxis);
        m_up.normalize();
        m_start = true;
    }
}

//Called Every Frame
void STCameraComponent::update() {
    auto input = STGame::Get()->getInput();
    auto transform = m_entity->transform();
    auto delta = input->getDelta();
    auto right = m_forward.cross(m_up);
    right.normalize();

    switch(m_viewProfile.m_moveMode){
        case STCameraProperties::MoveMode::FIRST_PERSON:
            updateCameraRotations(input);
            break;
        case STCameraProperties::MoveMode::FIRST_PERSON_FLY:
            updateCameraRotations(input);

            if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::FORWARD))){
                stReal x = transform->getTranslate().getX(),
                        y = transform->getTranslate().getY(),
                        z = transform->getTranslate().getZ();
                x += m_forward.getX() * m_speed * delta;
                y -= m_forward.getY() * m_speed * delta;
                z += m_forward.getZ() * m_speed * delta;
                transform->setTranslate({x, y, z});
            }

            if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::BACKWARD))){
                stReal x = transform->getTranslate().getX(),
                        y = transform->getTranslate().getY(),
                        z = transform->getTranslate().getZ();
                x -= m_forward.getX() * m_speed * delta;
                y += m_forward.getY() * m_speed * delta;
                z -= m_forward.getZ() * m_speed * delta;
                transform->setTranslate({x, y, z});
            }

            if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::STRAFE_LEFT))){
                stReal x = transform->getTranslate().getX(), z = transform->getTranslate().getZ();
                x += right.getX() * m_speed * delta;
                z += right.getZ() * m_speed * delta;
                transform->setTranslateX(x);
                transform->setTranslateZ(z);
            }

            if(input->isKeyDown(input->inputMapping()->get(MOVEMENT::STRAFE_RIGHT))){
                stReal x = transform->getTranslate().getX(), z = transform->getTranslate().getZ();
                x -= right.getX() * m_speed * delta;
                z -= right.getZ() * m_speed * delta;
                transform->setTranslateX(x);
                transform->setTranslateZ(z);
            }

            break;
        case STCameraProperties::MoveMode::THIRD_PERSON:
            //TODO implement this;
            break;
        case STCameraProperties::MoveMode::ISOMETRIC:

            break;
        case STCameraProperties::MoveMode::LOCKED:

            break;
        case STCameraProperties::MoveMode::CUSTOM:
            m_customUpdate(this, input);
            break;
        default:
            ;
    }
}

//Called in the Draw Loop
void STCameraComponent::draw() {

}

Matrix4f STCameraComponent::getViewProjection() const {
    return getProjection() * getView();
    return getProjection() * getView();
}

Matrix4f STCameraComponent::getView() const {
    Matrix4f Camera, TransformTranslate;
    Camera.initCamera(m_forward, m_up);
    auto trans = m_entity->transform()->getTranslate();
    TransformTranslate.initTranslation(-trans.getX(), trans.getY(), -trans.getZ());
    return Camera * TransformTranslate;
}

Matrix4f STCameraComponent::getProjection() const {
    Matrix4f ViewMode;
    if(m_viewProfile.m_viewMode == STCameraProperties::ViewMode::PERSPECTIVE){
        ViewMode.initPerpectiveProjection(m_viewProfile.FOV, m_width, m_height, m_viewProfile.zNear, m_viewProfile.zFar);
    }else{
        ViewMode.initOrthographicProjection(m_width, m_height, m_viewProfile.zNear, m_viewProfile.zFar);
    }
    return ViewMode;
}

Vector3D STCameraComponent::getForward() const {
    return m_forward;
}

Vector3D STCameraComponent::getUp() const {
    return m_up;
}

void STCameraComponent::centerCamera(Input *input) {
    input->centerMouseInWindow();
    m_hAngle = 0.0f;
    m_vAngle = 0.0f;
}

void STCameraComponent::setHAngle(stReal h) {
    m_hAngle = h;
}

void STCameraComponent::setVAngle(stReal v) {
    m_vAngle = v;
}

void STCameraComponent::updateCameraRotations(Input *input) {
    bool isCursorBound = input->isCursorBound();
    if(isCursorBound){
        m_hAngle -= input->getMouseSensitivity() * ((m_width / 2.f) - input->getMouseCoords().getX());
        m_vAngle -= input->getMouseSensitivity() * ((m_height / 2.f) - input->getMouseCoords().getY());
    }

    Vector3D vAxis(0.f, 1.f, 0.f);

    m_view = Vector3D(1.f, 0.f, 0.f);
    m_view.rotate(m_hAngle, vAxis);
    m_view.normalize();

    Vector3D hAxis = vAxis.cross(m_view);
    hAxis.normalize();
    m_view.rotate(m_vAngle, hAxis);

    m_forward = m_view;
    m_forward.normalize();

    m_up = m_forward.cross(hAxis);
    m_up.normalize();
    m_start = true;

    if(isCursorBound) input->centerMouseInWindow();
}

void STCameraComponent::setSpeed(stReal s) {
    m_speed = s;
}

void STCameraComponent::load(std::ifstream &in) {

}

void STCameraComponent::save(std::ofstream &out) {

}

void STCameraComponent::setCustomUpdate(std::function<void(STCameraComponent *, Input *input)> customUpdate) {
    m_customUpdate = customUpdate;
}




