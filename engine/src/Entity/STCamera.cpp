#include "STCamera.h"

STCamera::STCamera() {
    m_transform = std::make_shared<Transform>();
    numComponents = 0;
}


std::shared_ptr<STCamera> STCamera::Create(const std::string &filename) {
    return std::shared_ptr<STCamera>();
}

std::shared_ptr<STCamera> STCamera::Create(STCameraProperties::STViewProfile m_viewProfile, Vector3D startPosition) {
    auto ret = std::make_shared<STCamera>();
    ret->transform()->setTranslate(startPosition);
    auto comp = ret->addComponent<STCameraComponent>(new STCameraComponent(m_viewProfile));
    auto t = ret->shared_from_this();
    comp->init(t);

    return ret;
}
